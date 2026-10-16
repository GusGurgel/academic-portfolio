from sqlmodel import SQLModel, Field, Relationship
from typing import TYPE_CHECKING

from .project_user import ProjectUser

if TYPE_CHECKING:
    from .project import Project


class User(SQLModel, table=True):
    id: int | None = Field(default=None, primary_key=True)
    name: str
    email: str = Field(unique=True)
    projects: list["Project"] = Relationship(
        back_populates="users", link_model=ProjectUser
    )
