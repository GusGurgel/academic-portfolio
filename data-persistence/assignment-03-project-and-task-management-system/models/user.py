from pydantic import BaseModel
from beanie import Document
import pymongo


class UserBase(BaseModel):
    name: str
    email: str


class UserCreate(UserBase):
    pass


class UserUpdate(BaseModel):
    name: str | None = None
    email: str | None = None


class User(Document, UserBase):
    class Settings:
        indexes = [
            pymongo.IndexModel("email", unique=True),
        ]
        name = "users"