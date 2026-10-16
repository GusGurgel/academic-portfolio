from database import get_session
from models import (
    Task,
    TaskStatus,
    Project,
    TaskWithTaskStatus,
    User,
    ProjectWithUserAndTasks,
    ProjectUser,
)

from sqlmodel import select
from sqlalchemy.orm import joinedload


def create_project():
    with get_session() as session:
        project = Project(name="GutoBot", description="GutoBot")

        session.add(project)
        session.commit()
        session.refresh(project)

        print(project)


def create_task_status():
    with get_session() as session:
        task_status_1 = TaskStatus(name="done")

        session.add(task_status_1)
        session.commit()
        session.refresh(task_status_1)

        print(task_status_1)


def create_task():
    with get_session() as session:
        statement = select(TaskStatus).where(TaskStatus.name == "done")
        result = session.exec(statement)
        task_status = result.one()

        statement = select(Project).where(Project.name == "GutoBot")
        result = session.exec(statement)
        project = result.one()

        if task_status.id and project.id:
            task = Task(
                name="Lorem ipsum.",
                description="Lorem ipsum.",
                id_task_status=task_status.id,
                id_project=project.id,
            )

            session.add(task)
            session.commit()
            session.refresh(task)

            print(task)


def create_user():
    with get_session() as session:
        user = User(name="Gustavo Gurgel", email="gurgel@email.com")
        session.add(user)
        session.commit()
        session.refresh(user)

        print(user)


def read_task():
    with get_session() as session:
        statement = (
            select(Task)
            .where(Task.name == "Lorem ipsum.")
            .options(joinedload(Task.project), joinedload(Task.task_status))
        )
        result = session.exec(statement)
        task = result.one()

        task_with_relations = TaskWithTaskStatus.model_validate(task)

        # print(task.model_dump())
        print(task_with_relations.model_dump())


def read_project():
    with get_session() as session:
        statement = (
            select(Project)
            .where(Project.name == "GutoBot")
            .options(joinedload(Project.tasks), joinedload(Project.users))
        )
        result = session.exec(statement)
        project = result.unique().one()

        project_with_tasks_and_users = ProjectWithUserAndTasks.model_validate(project)

        # print(task.model_dump())
        print(project_with_tasks_and_users.model_dump())


# def create_user_project():
#     with get_session() as session:
#         statement = select(User).where(User.name == "Gustavo Gurgel")
#         result = session.exec(statement)
#         user = result.one()

#         statement = select(Project).where(Project.name == "GutoBot")
#         result = session.exec(statement)
#         project = result.one()

#         if project.id and user.id:
#             project_user = ProjectUser(id_project=project.id, id_user=user.id)
#             session.add(project_user)
#             session.commit()
#             session.refresh(project_user)
#             print(project_user)


# create_project()
# create_task_status()
# create_task()
# create_user()
# read_task()
# create_user_project()
read_project()
