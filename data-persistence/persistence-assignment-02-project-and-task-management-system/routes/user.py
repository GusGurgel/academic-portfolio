from fastapi import APIRouter, HTTPException, Depends, Query, status, Response
from sqlmodel import Session, select

from models import User, Project, ProjectUser
from database import get_session

router = APIRouter(
    prefix="/users",
    tags=["User"],
)


@router.post("/", response_model=User, status_code=status.HTTP_201_CREATED)
async def create_user(user: User, session: Session = Depends(get_session)):
    """
    Cria um novo usuário no banco de dados.
    """
    existing_user = session.exec(select(User).where(User.email == user.email)).first()
    if existing_user:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"User with email {user.email} already exists",
        )

    session.add(user)
    session.commit()
    session.refresh(user)
    return user


@router.get("/", response_model=list[User])
def get_users(
    offset: int = 0,
    limit: int = Query(default=10, le=100),
    session: Session = Depends(get_session),
):
    """
    Retorna uma lista de usuários com paginação.
    """
    statement = select(User).offset(offset).limit(limit)
    return session.exec(statement).all()


@router.get("/{id_user}", response_model=User)
def get_user_by_id(id_user: int, session: Session = Depends(get_session)):
    """
    Retorna um usuário específico pelo seu ID.
    Levanta 404 se não encontrado.
    """
    user = session.get(User, id_user)
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {id_user} not found")
    return user


@router.get("/{id_user}/projects", response_model=list[Project])
def get_user_projects(id_user: int, session: Session = Depends(get_session)):
    """
    Lista todos os projetos em que um usuário está alocado.
    """
    user = session.get(User, id_user)
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {id_user} not found")

    statement = (
        select(Project)
        .join(ProjectUser)
        .where(ProjectUser.id_user == id_user)
    )
    return session.exec(statement).all()



@router.put("/{user_id}", response_model=User)
def update_user(
    user_id: int, user_update: User, session: Session = Depends(get_session)
):
    """
    Atualiza completamente um usuário existente.
    """
    db_user = session.get(User, user_id)
    if not db_user:
        raise HTTPException(status_code=404, detail=f"User with id {user_id} not found")

    for key, value in user_update.model_dump(exclude_unset=True).items():
        setattr(db_user, key, value)

    session.add(db_user)
    session.commit()
    session.refresh(db_user)
    return db_user


@router.delete("/{user_id}", status_code=status.HTTP_204_NO_CONTENT)
def delete_user(user_id: int, session: Session = Depends(get_session)):
    """
    Deleta um usuário específico.
    """
    user = session.get(User, user_id)
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {user_id} not found")

    session.delete(user)
    session.commit()

    # O status 204 NO CONTENT não deve retornar corpo (o return {} é ignorado/opcional)
    return Response(status_code=status.HTTP_204_NO_CONTENT)
