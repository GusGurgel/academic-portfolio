from typing import TYPE_CHECKING
from sqlmodel import SQLModel, Field, Relationship

from .project_user import ProjectUser

if TYPE_CHECKING:
    from .user import User
    from .task import Task, TaskWithTaskStatus


class ProjectBase(SQLModel):
    id: int | None = Field(default=None, primary_key=True)
    name: str
    description: str | None = Field(default=None)


class Project(ProjectBase, table=True):
    tasks: list["Task"] = Relationship(back_populates="project")
    users: list["User"] = Relationship(
        back_populates="projects", link_model=ProjectUser
    )


class ProjectWithUserAndTasks(ProjectBase):
    users: list["User"] | None = None
    tasks: list["TaskWithTaskStatus"] | None = None
