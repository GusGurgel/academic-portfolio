from typing import TYPE_CHECKING
from datetime import date
from pydantic import BaseModel, Field
from beanie import Document, Link, PydanticObjectId

if TYPE_CHECKING:
    from .user import User
    from .task_status import TaskStatus

class TaskBase(BaseModel):
    name: str
    description: str | None = None
    due_date: date | None  = None
    priority: str | None = None

class TaskCreate(TaskBase):
    pass 

class TaskUpdate(BaseModel): 
    name: str | None = None
    description: str | None = None
    due_date: date | None = None
    priority: str | None = None
    
    status_id: PydanticObjectId | None = None

class Task(TaskBase):
    id: PydanticObjectId = Field(default_factory=PydanticObjectId)
    status: Link["TaskStatus"] | None  = None 

class ProjectBase(BaseModel):
    name: str
    description: str | None = None

class ProjectCreate(ProjectBase):
    tasks: list[Task] = []
    users: list[PydanticObjectId] = [] 

class ProjectUpdate(BaseModel):
    name: str | None = None
    description: str | None = None
    tasks: list[Task] | None = None
    users: list[PydanticObjectId] | None = None
class Project(Document, ProjectBase):
    tasks: list["Task"] = []
    users: list[Link["User"]] = []

    class Settings:
        name = "projects"

from .user import User
from .task_status import TaskStatus

Task.model_rebuild()
Project.model_rebuild()