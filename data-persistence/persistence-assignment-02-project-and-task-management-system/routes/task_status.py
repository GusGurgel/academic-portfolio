from fastapi import APIRouter, HTTPException, Depends, Query, status, Response
from sqlmodel import Session, select

from models import TaskStatus
from database import get_session

router = APIRouter(
    prefix="/task-status",
    tags=["Task Status"],
)


@router.post("/", response_model=TaskStatus)
async def create_task_status(
    task_status: TaskStatus, session: Session = Depends(get_session)
):
    """
    Cria um novo status de tarefa no banco de dados.
    """
    session.add(task_status)
    session.commit()
    session.refresh(task_status)
    return task_status


@router.get("/", response_model=list[TaskStatus])
def get_task_status(
    offset: int = 0,
    limit: int = Query(default=10, le=100),
    session: Session = Depends(get_session),
):
    """
    Retorna uma lista de status de tarefas com paginação.
    """
    statement = select(TaskStatus).offset(offset).limit(limit)
    return session.exec(statement).all()


@router.get("/{task_status_id}", response_model=TaskStatus)
def get_task_status_by_id(task_status_id: int, session: Session = Depends(get_session)):
    """
    Retorna um status de tarefa específico pelo seu ID.
    Levanta 404 se não encontrado.
    """
    statement = select(TaskStatus).where(TaskStatus.id == task_status_id)
    task_status = session.exec(statement).first()
    if not task_status:
        raise HTTPException(
            status_code=404, detail=f"TaskStatus with id {task_status_id} not found"
        )
    return task_status


@router.put("/{task_status_id}", response_model=TaskStatus)
def update_task_status(
    task_status_id: int,
    task_status: TaskStatus,
    session: Session = Depends(get_session),
):
    """
    Atualiza completamente um status de tarefa existente pelo seu ID.
    Levanta 404 se não encontrado.
    """
    db_task_status = session.get(TaskStatus, task_status_id)
    if not db_task_status:
        raise HTTPException(
            status_code=404, detail=f"TaskStatus with id {task_status_id} not found"
        )
    for key, value in task_status.model_dump(exclude_unset=True).items():
        setattr(db_task_status, key, value)
    session.add(db_task_status)
    session.commit()
    session.refresh(db_task_status)
    return db_task_status


@router.delete("/{task_status_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_task_status(task_status_id: int, session: Session = Depends(get_session)):
    """
    Deleta um status de tarefa específico pelo seu ID.
    Levanta 404 se não encontrado.
    Levanta 400 se houver tarefas vinculadas a este status.
    """
    task_status = session.get(TaskStatus, task_status_id)
    
    if not task_status:
        raise HTTPException(
            status_code=status.HTTP_404_NOT_FOUND, 
            detail=f"TaskStatus with id {task_status_id} not found"
        )
    
    if task_status.tasks:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=(
                f"Cannot delete TaskStatus '{task_status.name}' (id: {task_status_id}) "
                f"because it is being used by {len(task_status.tasks)} task(s). "
                "Please reassign or delete the tasks first."
            )
        )

    session.delete(task_status)
    session.commit()
    
    return Response(status_code=status.HTTP_204_NO_CONTENT)