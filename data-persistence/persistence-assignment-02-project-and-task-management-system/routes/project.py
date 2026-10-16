from datetime import date
from fastapi import APIRouter, HTTPException, Depends, Query, status, Response
from sqlmodel import Session, select
from sqlalchemy.orm import joinedload, selectinload

from models import (
    Project,
    Task,
    ProjectWithUserAndTasks,
    TaskStatus,
    TaskWithTaskStatus,
    User,
    ProjectUser,
)
from database import get_session

router = APIRouter(
    prefix="/project",
    tags=["Project"],
)


@router.post("/", response_model=Project, summary="Criar novo projeto")
def create_project(project: Project, session: Session = Depends(get_session)):
    """
    Cria um novo projeto no banco de dados.
    """
    session.add(project)
    session.commit()
    session.refresh(project)
    return project


@router.get(
    "/search",
    response_model=list[ProjectWithUserAndTasks],
    summary="Pesquisar projetos",
)
def search_projects(
    name: str | None = Query(default=None, description="Nome do projeto"),
    description: str | None = Query(default=None, description="Descrição do projeto"),
    session: Session = Depends(get_session),
):
    """
    Pesquisa projetos por nome ou descrição.
    """
    statement = select(Project)
    if name:
        statement = statement.where(Project.name.ilike(f"%{name}%"))  # type: ignore
    if description:
        statement = statement.where(Project.description.ilike(f"%{description}%"))  # type: ignore

    statement.options(
        selectinload(Project.users),  # type: ignore
        selectinload(Project.tasks).joinedload(Task.task_status),  # type: ignore
    )

    return session.exec(statement).unique().all()


@router.get(
    "/",
    response_model=list[ProjectWithUserAndTasks],
    summary="Listar todos os projetos",
)
def get_projects(
    offset: int = 0,
    limit: int = Query(default=10, le=100),
    session: Session = Depends(get_session),
):
    """
    Lista os projetos cadastrados com paginação.
    """
    statement = (
        select(Project)
        .options(
            joinedload(Project.users),  # type: ignore
            joinedload(Project.tasks).joinedload(Task.task_status),  # type: ignore
        )
        .limit(limit)
        .offset(offset)
    )
    result = session.exec(statement)
    return result.unique().all()


@router.get(
    "/{id_project}",
    response_model=ProjectWithUserAndTasks,
    summary="Buscar projeto por ID",
)
def get_project(id_project: int, session: Session = Depends(get_session)):
    """
    Busca um projeto específico pelo seu ID.
    """
    statement = (
        select(Project)
        .where(Project.id == id_project)
        .options(
            joinedload(Project.users),  # type: ignore
            joinedload(Project.tasks).joinedload(Task.task_status),  # type: ignore
        )
    )
    project = session.exec(statement).first()
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")
    return project


@router.put("/{id_project}", response_model=Project, summary="Atualizar projeto")
def update_project(
    id_project: int, project_data: Project, session: Session = Depends(get_session)
):
    """
    Atualiza os dados de um projeto existente.
    """
    db_project = session.get(Project, id_project)
    if not db_project:
        raise HTTPException(status_code=404, detail="Project not found")

    project_dict = project_data.model_dump(exclude_unset=True)
    for key, value in project_dict.items():
        setattr(db_project, key, value)

    session.add(db_project)
    session.commit()
    session.refresh(db_project)
    return db_project


@router.delete("/{project_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_project(project_id: int, session: Session = Depends(get_session)):
    """
    Deleta um projeto específico.
    Retorna erro se houver tarefas ou usuários vinculados.
    """
    # 1. Buscar o projeto
    project = session.get(Project, project_id)

    if not project:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND, detail="Project not found"
        )

    # 2. Verificar vínculos
    errors = []

    if project.tasks:
        errors.append(f"possui {len(project.tasks)} tarefa(s) vinculada(s)")

    if project.users:
        errors.append(f"possui {len(project.users)} usuário(s) vinculado(s)")

    # 3. Se houver qualquer vínculo, impedir a deleção e informar o usuário
    if errors:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"Não é possível deletar o projeto '{project.name}': "
            + " e ".join(errors)
            + ".",
        )

    # 4. Se estiver limpo, deletar
    session.delete(project)
    session.commit()

    return Response(status_code=status.HTTP_204_NO_CONTENT)


# ==========
#   TASKS  |
# ==========


@router.post(
    "/{id_project}/task",
    response_model=TaskWithTaskStatus,
    summary="Adicionar tarefa ao projeto",
)
def create_task_for_project(
    id_project: int,
    task: Task,
    task_status: TaskStatus,
    session: Session = Depends(get_session),
):
    """
    Cria uma nova tarefa vinculada a um projeto específico.
    """
    if isinstance(task.due_date, str):
        task.due_date = date.fromisoformat(task.due_date)

    project = session.get(Project, id_project)
    if not project:
        raise HTTPException(status_code=404, detail="Project not found")

    task_status_db = session.exec(
        select(TaskStatus).where(TaskStatus.name == task_status.name)
    ).first()

    if task_status_db:
        final_status = task_status_db
    else:
        task_status.id = None
        session.add(task_status)
        session.commit()
        session.refresh(task_status)
        final_status = task_status

    if final_status.id:
        task.id_task_status = final_status.id
    task.id_project = id_project

    session.add(task)
    session.commit()
    session.refresh(task)
    return task


@router.get(
    "/task/search",
    response_model=list[TaskWithTaskStatus],
    summary="Pesquisar tarefas",
)
def search_tasks(
    name: str | None = Query(default=None, description="Nome da tarefa"),
    description: str | None = Query(default=None, description="Descrição da tarefa"),
    status: str | None = Query(default=None, description="Status da tarefa"),
    priority: str | None = Query(default=None, description="Prioridade da tarefa"),
    due_date: date | None = Query(default=None, description="Data de vencimento"),
    overdue: bool = Query(default=False, description="Filtrar tarefas atrasadas"),
    session: Session = Depends(get_session),
):
    """
    Pesquisa tarefas globalmente por nome, descrição, status ou data de vencimento.
    """
    statement = select(Task).options(joinedload(Task.task_status))  # type: ignore

    if name:
        statement = statement.where(Task.name.ilike(f"%{name}%"))  # type: ignore
    if description:
        statement = statement.where(Task.description.ilike(f"%{description}%"))  # type: ignore
    if status:
        statement = statement.join(TaskStatus).where(
            TaskStatus.name.ilike(f"%{status}%")  # type: ignore
        )  # type: ignore
    if priority:
        statement = statement.where(Task.priority.ilike(f"%{priority}%"))  # type: ignore
    if due_date:
        statement = statement.where(Task.due_date == due_date)
    if overdue:
        if not status:
            statement = statement.join(TaskStatus)
        statement = statement.where(Task.due_date < date.today())  # type: ignore
        statement = statement.where(TaskStatus.name != "Concluído")
    return session.exec(statement).all()


@router.get(
    "/{id_project}/task",
    response_model=list[TaskWithTaskStatus],
    summary="Listar tarefas do projeto",
)
def get_tasks_from_project(
    id_project: int,
    offset: int = 0,
    limit: int = Query(default=10, le=100),
    session: Session = Depends(get_session),
):
    """
    Lista todas as tarefas de um projeto específico.
    """
    statement = (
        select(Task)
        .where(Task.id_project == id_project)
        .options(joinedload(Task.task_status))  # type: ignore
        .limit(limit)
        .offset(offset)
    )
    return session.exec(statement).all()


@router.put(
    "/{id_project}/task/{id_task}", response_model=Task, summary="Atualizar tarefa"
)
def update_task_for_project(
    id_project: int,
    id_task: int,
    task_data: Task,
    session: Session = Depends(get_session),
):
    """
    Atualiza uma tarefa específica dentro de um projeto.
    """
    db_task = session.get(Task, id_task)
    if not db_task or db_task.id_project != id_project:
        raise HTTPException(status_code=404, detail="Task not found in this project")

    task_dict = task_data.model_dump(exclude_unset=True)
    for key, value in task_dict.items():
        setattr(db_task, key, value)

    session.add(db_task)
    session.commit()
    session.refresh(db_task)
    return db_task


@router.delete(
    "/{id_project}/task/{id_task}",
    status_code=status.HTTP_204_NO_CONTENT,
    summary="Deletar tarefa",
)
def delete_task_from_project(
    id_project: int, id_task: int, session: Session = Depends(get_session)
):
    """
    Remove uma tarefa de um projeto.
    """
    db_task = session.get(Task, id_task)
    if not db_task or db_task.id_project != id_project:
        raise HTTPException(status_code=404, detail="Task not found in this project")

    session.delete(db_task)
    session.commit()
    return None


# =========
#   USER  |
# =========


@router.post(
    "/{id_project}/user/{id_user}",
    response_model=User,
    summary="Adicionar usuário ao projeto",
)
def add_user_to_project(
    id_project: int, id_user: int, session: Session = Depends(get_session)
):
    """
    Vincula um usuário existente a um projeto existente.

    Se a relação já existir, retorna o usuário sem duplicar o vínculo.
    """
    project = session.get(Project, id_project)
    user = session.get(User, id_user)

    if not project or not user:
        raise HTTPException(status_code=404, detail="Project or User not found")

    link_exists = session.exec(
        select(ProjectUser).where(
            ProjectUser.id_project == id_project, ProjectUser.id_user == id_user
        )
    ).first()

    if not link_exists:
        project_user = ProjectUser(id_project=id_project, id_user=id_user)
        session.add(project_user)
        session.commit()

    return user


@router.get(
    "/{id_project}/user",
    response_model=list[User],
    summary="Listar usuários do projeto",
)
def get_users_from_project(
    id_project: int,
    offset: int = 0,
    limit: int = Query(default=10, le=100),
    session: Session = Depends(get_session),
):
    """
    Lista todos os usuários vinculados a um projeto.
    """

    statement = (
        select(User)
        .join(ProjectUser)
        .where(ProjectUser.id_project == id_project)
        .limit(limit)
        .offset(offset)
    )
    return session.exec(statement).all()


@router.delete(
    "/{id_project}/user/{id_user}",
    status_code=status.HTTP_204_NO_CONTENT,
    summary="Remover usuário do projeto",
)
def remove_user_from_project(
    id_project: int, id_user: int, session: Session = Depends(get_session)
):
    """
    Remove o vínculo de um usuário com um projeto.
    """
    link = session.exec(
        select(ProjectUser).where(
            ProjectUser.id_project == id_project, ProjectUser.id_user == id_user
        )
    ).first()

    if not link:
        raise HTTPException(
            status_code=404, detail="User is not assigned to this project"
        )

    session.delete(link)
    session.commit()
    return None
