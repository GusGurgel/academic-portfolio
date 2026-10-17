from fastapi import APIRouter, HTTPException, status, Response
from beanie import PydanticObjectId
from fastapi_pagination import Page
from fastapi_pagination.ext.beanie import apaginate

from models.task_status import TaskStatus, TaskStatusCreate, TaskStatusUpdate

router = APIRouter(
    prefix="/task-status",
    tags=["Task Status"],
)


@router.post("/", response_model=TaskStatus, status_code=status.HTTP_201_CREATED)
async def create_task_status(task_status_data: TaskStatusCreate) -> TaskStatus:
    task_status = TaskStatus(**task_status_data.model_dump())
    await task_status.create()
    return task_status


@router.get("/", response_model=Page[TaskStatus])
async def get_task_status() -> Page[TaskStatus]:
    return await apaginate(TaskStatus.find_all())


@router.get("/{task_status_id}", response_model=TaskStatus)
async def get_task_status_by_id(task_status_id: PydanticObjectId) -> TaskStatus:
    task_status = await TaskStatus.get(task_status_id)
    if not task_status:
        raise HTTPException(
            status_code=404, detail=f"TaskStatus with id {task_status_id} not found"
        )
    return task_status


@router.put("/{task_status_id}", response_model=TaskStatus)
async def update_task_status(
    task_status_id: PydanticObjectId, task_status_update: TaskStatusUpdate
) -> TaskStatus:
    task_status = await TaskStatus.get(task_status_id)
    if not task_status:
        raise HTTPException(
            status_code=404, detail=f"TaskStatus with id {task_status_id} not found"
        )

    data_to_update = task_status_update.model_dump(exclude_unset=True)
    for key, value in data_to_update.items():
        setattr(task_status, key, value)

    await task_status.save()
    return task_status


@router.delete("/{task_status_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_task_status(task_status_id: PydanticObjectId):
    task_status = await TaskStatus.get(task_status_id)

    if not task_status:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND,
            detail=f"TaskStatus with id {task_status_id} not found",
        )

    await task_status.delete()
    return Response(status_code=status.HTTP_204_NO_CONTENT)
