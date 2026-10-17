from sqlmodel import SQLModel, Field, Relationship
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .task import Task


class TaskStatus(SQLModel, table=True):
    id: int | None = Field(default=None, primary_key=True)
    name: str
    tasks: list["Task"] = Relationship(back_populates="task_status")
