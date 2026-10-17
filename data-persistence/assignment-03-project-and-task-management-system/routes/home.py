from fastapi import APIRouter

router = APIRouter(
    prefix="",
    tags=["Home"],
)


@router.get("/")
async def root():
    """
    Basic root message.
    """
    return {"msg": "Bem-vindo ao FastAPI!"}
