from typing import List, Literal
from datetime import date, datetime
from fastapi import APIRouter, HTTPException, Query, status, Response
from beanie import PydanticObjectId
from beanie.operators import RegEx, Or

from models.project import Project, ProjectCreate, ProjectUpdate, Task, TaskCreate, TaskUpdate
from models.user import User
from models.task_status import TaskStatus

router = APIRouter(
    prefix="/projects",
    tags=["Projects"],
)

# =============
#   PROJECTS  |
# =============

@router.post("/", response_model=Project, status_code=status.HTTP_201_CREATED)
async def create_project(project_data: ProjectCreate):
    new_project = Project(**project_data.model_dump())
    await new_project.create()
    return new_project

@router.get("/", response_model=List[Project])
async def get_projects(
    offset: int = 0,
    limit: int = Query(default=10, le=100),
    sort_by: Literal["name", "description"] = "name",
    order: Literal["asc", "desc"] = "asc",
    name: str | None = Query(default=None),
    description: str | None = Query(default=None),
):
    sort_expr = sort_by if order == "asc" else f"-{sort_by}"

    query_filters = []
    if name:
        query_filters.append(RegEx(Project.name, name, "i"))
    if description:
        query_filters.append(RegEx(Project.description, description, "i"))

    query = Project.find_all(fetch_links=True) if not query_filters else Project.find(
        Or(*query_filters),
        fetch_links=True,
    )

    return (
        await query
        .sort(sort_expr)
        .skip(offset)
        .limit(limit)
        .to_list()
    )

@router.get("/reports")
async def get_projects_overdue_report():
    now = datetime.now()

    pipeline = [
        {"$match": {"tasks": {"$exists": True, "$not": {"$size": 0}}}},

        {"$unwind": "$tasks"},

        {"$group": {
            "_id": "$_id", 
            "project_name": {"$first": "$name"},
            "total_tasks": {"$sum": 1},
            "overdue_tasks": {
                "$sum": {
                    "$cond": [
                        {"$and": [
                            {"$ifNull": ["$tasks.due_date", False]}, 
                            {"$lt": ["$tasks.due_date", now]}
                        ]}, 
                        1, 
                        0
                    ]
                }
            }
        }},

        {"$project": {
            "_id": 0,
            "id": {"$toString": "$_id"},
            "project_name": 1,
            "total_tasks": 1,
            "overdue_tasks": 1,
        }},

        {"$sort": {"overdue_tasks": -1}}
    ]

    return await Project.aggregate(pipeline).to_list()

@router.get("/{id_project}", response_model=Project)
async def get_project(id_project: PydanticObjectId):
    project = await Project.get(id_project, fetch_links=True)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")
    return project

@router.put("/{id_project}", response_model=Project)
async def update_project(id_project: PydanticObjectId, project_data: ProjectUpdate):
    project = await Project.get(id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")
    
    data_to_update = project_data.model_dump(exclude_unset=True, exclude={"id", "tasks", "users"})
    
    await project.set(data_to_update)
    return project

@router.delete("/{id_project}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_project(id_project: PydanticObjectId):
    project = await Project.get(id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")

    errors = []
    if project.tasks:
        errors.append(f"possui {len(project.tasks)} tarefa(s)")
    if project.users:
        errors.append(f"possui {len(project.users)} usuário(s)")
    
    if errors:
        raise HTTPException(
            status_code=400, 
            detail=f"Não é possível deletar: O projeto " + " e ".join(errors)
        )

    await project.delete()
    return Response(status_code=status.HTTP_204_NO_CONTENT)


# =============
#    TASKS    |
# =============

@router.post("/{id_project}/task", response_model=Task)
async def create_task(
    id_project: PydanticObjectId,
    task_data: TaskCreate,
    id_task_status: PydanticObjectId
):
    task = Task(**task_data.model_dump())

    project = await Project.get(id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")

    status_obj = await TaskStatus.get(id_task_status)
    if not status_obj:
        raise HTTPException(status_code=404, detail="Task Status not found")
    
    task.status = status_obj
    task.id = PydanticObjectId() 

    await project.update({"$push": {"tasks": task.model_dump()}})
    
    return task

@router.get("/{id_project}/tasks", response_model=List[Task])
async def list_project_tasks(
    id_project: PydanticObjectId,
    name: str | None = Query(default=None, description="Filtrar por nome"),
    description: str | None = Query(default=None, description="Filtrar por descrição"),
    start_date: date | None = Query(default=None, description="A partir desta data (inclusive)"),
    end_date: date | None = Query(default=None, description="Até esta data (inclusive)"),
):
    pipeline = [
        {"$match": {"_id": id_project}},
        {"$unwind": "$tasks"},
    ]

    match_conditions = {}

    if name:
        match_conditions["tasks.name"] = {"$regex": name, "$options": "i"}
    
    if description:
        match_conditions["tasks.description"] = {"$regex": description, "$options": "i"}

    date_query = {}
    
    if start_date:
        date_query["$gte"] = datetime(start_date.year, start_date.month, start_date.day)
        
    if end_date:
        date_query["$lte"] = datetime(end_date.year, end_date.month, end_date.day)
    
    if date_query:
        match_conditions["tasks.due_date"] = date_query

    if match_conditions:
        pipeline.append({"$match": match_conditions})

    pipeline.append({"$replaceRoot": {"newRoot": "$tasks"}})

    return await Project.aggregate(pipeline).to_list()

@router.put("/{id_project}/tasks/{id_task}", response_model=Task)
async def update_task(
    id_project: PydanticObjectId,
    id_task: PydanticObjectId,
    task_update: TaskUpdate,
):
    project = await Project.get(id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")

    task_found = False
    for i, task in enumerate(project.tasks):
        if task.id == id_task:
            task_found = True
            
            update_data = task_update.model_dump(exclude_unset=True, exclude={"id", "status"})
            current_data = task.model_dump()
            current_data.update(update_data)
            
            new_task = Task(**current_data)
            
            if task_update.status_id:
                new_status = await TaskStatus.get(task_update.status_id)
                if not new_status:
                    raise HTTPException(404, "New status not found")
                new_task.status = new_status
            else:
                new_task.status = task.status

            project.tasks[i] = new_task
            break
    
    if not task_found:
        raise HTTPException(status_code=404, detail="Task not found in project")

    await project.save()
    
    await project.fetch_link("tasks.status") 
    
    for t in project.tasks:
        if t.id == id_task:
            return t


@router.delete("/{id_project}/tasks/{id_task}", status_code=204)
async def delete_task(id_project: PydanticObjectId, id_task: PydanticObjectId):
    project = await Project.get(id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")

    await project.update({"$pull": {"tasks": {"id": id_task}}})
    
    return Response(status_code=status.HTTP_204_NO_CONTENT)


# =========
#   USER  |
# =========


@router.post("/{id_project}/users/{id_user}")
async def add_user_to_project(id_project: PydanticObjectId, id_user: PydanticObjectId):
    project = await Project.get(id_project)
    user = await User.get(id_user)
    
    if not project or not user:
        raise HTTPException(status_code=404, detail="Project or User not found")

    if any(u.ref.id == user.id for u in project.users if u.ref):
        raise HTTPException(status_code=400, detail="User already in project")

    project.users.append(user)
    await project.save()
    
    return {"message": "User added successfully"}

@router.delete("/{id_project}/users/{id_user}", status_code=204)
async def remove_user_from_project(id_project: PydanticObjectId, id_user: PydanticObjectId):
    project = await Project.get(id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")

    original_len = len(project.users)
    project.users = [u for u in project.users if u.ref.id != id_user]
    
    if len(project.users) == original_len:
         raise HTTPException(status_code=404, detail="User not linked to this project")

    await project.save()
    return Response(status_code=status.HTTP_204_NO_CONTENT)