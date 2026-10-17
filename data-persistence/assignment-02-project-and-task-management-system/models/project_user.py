from sqlmodel import SQLModel, Field


class ProjectUser(SQLModel, table=True):
    id_project: int = Field(default=None, foreign_key="project.id", primary_key=True)
    id_user: int = Field(default=None, foreign_key="user.id", primary_key=True)
