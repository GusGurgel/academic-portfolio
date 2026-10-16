from fastapi import FastAPI

from routes import home, task_status, project, user

# Inicializa o aplicativo FastAPI
app = FastAPI()

# Rotas para Endpoints
app.include_router(home.router)
app.include_router(task_status.router)
app.include_router(project.router)
app.include_router(user.router)
