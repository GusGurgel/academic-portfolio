from pydantic import BaseModel
from beanie import Document


class TaskStatusBase(BaseModel):
    name: str


class TaskStatusCreate(TaskStatusBase):
    pass


class TaskStatusUpdate(BaseModel):
    name: str | None = None


class TaskStatus(Document, TaskStatusBase):
    class Settings:
        name = "task_status"