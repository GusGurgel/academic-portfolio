from fastapi import APIRouter, HTTPException, status, Response
from beanie import PydanticObjectId
from fastapi_pagination import Page
from fastapi_pagination.ext.beanie import apaginate
from pymongo.errors import DuplicateKeyError

from models.user import User, UserCreate, UserUpdate

router = APIRouter(
    prefix="/users",
    tags=["Users"],
)


@router.post("/", response_model=User, status_code=status.HTTP_201_CREATED)
async def create_user(user_data: UserCreate) -> User:
    try:
        user = User(**user_data.model_dump())
        await user.create()
    except DuplicateKeyError:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"User with email {user.email} already exists",
        )
    return user


@router.get("/", response_model=Page[User])
async def get_users() -> Page[User]:
    return await apaginate(User.find_all())


@router.get("/{user_id}", response_model=User)
async def get_user_by_id(user_id: PydanticObjectId) -> User:
    user = await User.get(user_id)
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {user_id} not found")
    return user


@router.put("/{user_id}", response_model=User)
async def update_user(user_id: PydanticObjectId, user_update: UserUpdate) -> User:
    user = await User.get(user_id)
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {user_id} not found")

    try:
        data_to_update = user_update.model_dump(exclude_unset=True)

        for field, value in data_to_update.items():
            setattr(user, field, value)

        await user.save()
        return user
    except DuplicateKeyError:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="User with this email already exists",
        )


@router.delete("/{user_id}", status_code=status.HTTP_204_NO_CONTENT)
async def delete_user(user_id: PydanticObjectId):
    user = await User.get(user_id)
    if not user:
        raise HTTPException(status_code=404, detail=f"User with id {user_id} not found")

    await user.delete()
    return Response(status_code=status.HTTP_204_NO_CONTENT)
