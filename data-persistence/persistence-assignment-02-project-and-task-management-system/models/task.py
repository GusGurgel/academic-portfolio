from datetime import date as date_type
from sqlmodel import SQLModel, Field, Relationship
from .task_status import TaskStatus
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from .project import Project


class TaskBase(SQLModel):
    id: int | None = Field(default=None, primary_key=True)
    name: str
    description: str | None = Field(default=None)
    due_date: date_type | None = Field(default=None)
    priority: str | None = Field(default=None)


class Task(TaskBase, table=True):
    id_task_status: int = Field(foreign_key="taskstatus.id")
    task_status: TaskStatus = Relationship(back_populates="tasks")
    id_project: int = Field(foreign_key="project.id")
    project: "Project" = Relationship(back_populates="tasks")


class TaskWithTaskStatus(TaskBase):
    task_status: TaskStatus | None = None
