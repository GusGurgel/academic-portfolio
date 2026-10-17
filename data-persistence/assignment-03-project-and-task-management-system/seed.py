import asyncio
import os
import random
from dotenv import load_dotenv

from motor.motor_asyncio import AsyncIOMotorClient
from beanie import init_beanie, PydanticObjectId
from faker import Faker

from models.user import User
from models.project import Project, Task
from models.task_status import TaskStatus

load_dotenv()
fake = Faker("pt_BR")

DATABASE_URL = os.getenv("DATABASE_URL")
DB_NAME = os.getenv("DBNAME", "trabalho-persistencia-3")

async def init_db():
    client = AsyncIOMotorClient(DATABASE_URL)
    await init_beanie(
        database=client[DB_NAME],
        document_models=[User, Project, TaskStatus]
    )

# ==========================================
# GERAÇÃO DE STATUS
# ==========================================
async def generate_task_status():
    kanban_stages = [
        "Backlog", "Refinamento", "A Fazer", "Bloqueado", 
        "Em Desenvolvimento", "Code Review", "QA/Testes", 
        "Homologação", "Deploy", "Concluído"
    ]

    if await TaskStatus.find_all().count() > 0:
        return await TaskStatus.find_all().to_list()

    status_list = []
    for stage in kanban_stages:
        status = TaskStatus(
            name=stage,
            description=f"Tarefas na etapa de {stage}"
        )
        await status.create()
        status_list.append(status)
    
    return status_list

# ==========================================
# GERAÇÃO DE USUÁRIOS
# ==========================================

async def generate_users():
    if await User.find_all().count() > 0:
        return await User.find_all().to_list()

    users_list = []
    for _ in range(15):
        user = User(
            name=fake.name(),
            email=fake.email()
        )
        await user.create()
        users_list.append(user)
    
    return users_list

# ==========================================
# GERAÇÃO DE DADOS DAS TAREFAS
# ==========================================

def generate_tasks_data(qtd, status_list):
    """
    Gera uma lista de objetos Task
    """
    verbos = [
        "Implementar", "Corrigir", "Refatorar", "Testar", "Documentar",
        "Otimizar", "Atualizar", "Configurar", "Analisar", "Desenhar"
    ]

    key_words = [
        "Autenticação JWT", "Endpoint de Usuários", "CSS da Home",
        "Banco de Dados", "Docker Compose", "Pipeline de CI/CD",
        "Tela de Login", "Botão de Logout", "Relatório PDF",
        "Integração com API", "Cache Redis", "Migração do Banco",
        "Validação de Formulário", "Rodapé do Site", "Microserviço de Email"
    ]

    prioridades = ["Baixa", "Média", "Alta", "Crítica"]
    
    tasks_objs = []
    
    for _ in range(qtd):
        random_status = random.choice(status_list)
        name_task = f"{random.choice(verbos)} {random.choice(key_words)}"
        
        random_date = fake.date_between(start_date="-2d", end_date="+30d")

        task = Task(
            id=PydanticObjectId(),
            name=name_task,
            description=f"Descrição detalhada para: {name_task}",
            due_date=random_date,
            priority=random.choice(prioridades),
            status=random_status
        )
        tasks_objs.append(task)
        
    return tasks_objs

# ==========================================
# GERAÇÃO DE PROJETOS
# ==========================================
async def generate_projects(users_list, status_list):
    
    await Project.delete_all()
    
    projects_list = []
    total_tasks_count = 0

    for _ in range(10):
        qtd_tasks = random.randint(3, 8)
        project_tasks = generate_tasks_data(qtd_tasks, status_list)
        total_tasks_count += qtd_tasks

        team_members = random.sample(users_list, k=random.randint(2, 5))

        project = Project(
            name=f"Projeto {fake.bs().title()}",
            description=fake.catch_phrase(),
            tasks=project_tasks,
            users=team_members
        )
        
        await project.create()
        projects_list.append(project)

    return projects_list, total_tasks_count

async def seed_data():
    await init_db()

    status_list = await generate_task_status()
    users_list = await generate_users()
    
    projects_list, tasks_count = await generate_projects(users_list, status_list)

    print(f"{len(users_list)} Usuários no banco.")
    print(f"{len(status_list)} Status criados.")
    print(f"{len(projects_list)} Projetos criados.")
    print(f"{tasks_count} Tarefas distribuídas.")

if __name__ == "__main__":
    if not DATABASE_URL:
        print("Erro no .env")
    else:
        asyncio.run(seed_data())