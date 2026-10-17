import random
from sqlmodel import Session, select
from faker import Faker
from database import engine

from models.user import User
from models.project import Project
from models.task import Task
from models.task_status import TaskStatus

fake = Faker("pt_BR")


def generate_task_status(session):
    kanban_stages = [
        "Backlog",
        "Refinamento",
        "A Fazer",
        "Bloqueado",
        "Em Desenvolvimento",
        "Code Review",
        "QA/Testes",
        "Homologação",
        "Deploy",
        "Concluído",
    ]

    # TaskStatus
    status_list = []
    if not session.exec(select(TaskStatus)).first():
        for stage in kanban_stages:
            status = TaskStatus(
                name=stage,
                description=f"Tarefas na etapa de {stage}",
            )
            session.add(status)
            status_list.append(status)
        session.commit()
        for s in status_list:
            session.refresh(s)
    else:
        status_list = session.exec(select(TaskStatus)).all()
    return status_list


def generate_users(session):
    # Usuarios
    users_list = []
    if not session.exec(select(User)).first():
        for _ in range(15):
            user = User(name=fake.name(), email=fake.email())
            session.add(user)
            users_list.append(user)
        session.commit()
        for u in users_list:
            session.refresh(u)
    else:
        users_list = session.exec(select(User)).all()
    return users_list


def generate_projects(session, users_list=[]):
    # Projetos
    projects_list = []
    for _ in range(10):
        project = Project(
            name=f"Projeto {fake.bs().title()}", description=fake.catch_phrase()
        )

        # Relacionamento com usuarios
        team_members = random.sample(users_list, k=random.randint(2, 4))
        project.users = team_members

        session.add(project)
        projects_list.append(project)

    session.commit()
    for p in projects_list:
        session.refresh(p)
    return projects_list


def generate_tasks(session, status_list=[], projects_list=[]):
    # Tasks
    tasks_count = 0
    verbos = [
        "Implementar",
        "Corrigir",
        "Refatorar",
        "Testar",
        "Documentar",
        "Otimizar",
        "Atualizar",
        "Configurar",
    ]

    key_words = [
        "Autenticação JWT",
        "Endpoint de Usuários",
        "CSS da Home",
        "Banco de Dados",
        "Docker Compose",
        "Pipeline de CI/CD",
        "Tela de Login",
        "Botão de Logout",
        "Relatório PDF",
        "Integração com API",
        "Cache Redis",
        "Migração do Banco",
        "Validação de Formulário",
        "Rodapé do Site",
    ]

    prioridades = ["Baixa", "Média", "Alta", "Crítica"]

    for project in projects_list:
        for _ in range(random.randint(2, 5)):
            random_status = random.choice(status_list)

            name_task = f"{random.choice(verbos)} {random.choice(key_words)}"
            random_date = fake.date_between(start_date="-2d", end_date="+30d")

            task = Task(
                name=name_task,
                description=name_task,
                id_project=project.id,
                id_task_status=random_status.id,
                due_date=random_date,
                priority=random.choice(prioridades),
            )
            session.add(task)
            tasks_count += 1
    return tasks_count


def seed_data():
    with Session(engine) as session:
        status_list = generate_task_status(session)
        users_list = generate_users(session)
        projects_list = generate_projects(session, users_list)
        tasks_count = generate_tasks(session, status_list, projects_list)

        session.commit()
        print(
            f"Gerados: {len(users_list)} Usuários, {len(projects_list)} Projetos e {tasks_count} Tarefas."
        )


if __name__ == "__main__":
    seed_data()
