# Project and Task Management System

This repository contains the final project for the **Persistence** course at the Federal University of Ceará (UFC), Brazil.

The goal is to build a robust API using **FastAPI** and **SQLModel**, demonstrating knowledge of data modeling, relationships (one-to-many and many-to-many), database migrations, and complex queries, with support for both **SQLite** and **PostgreSQL**.

## 👥 Team

| Student ID | Name                              | Email                         |
| :--------: | :-------------------------------- | :---------------------------- |
| 539226     | **Gustavo Gurgel Medeiros**       | gusgurgel@alu.ufc.br          |
| 536536     | **Matheus Conrado Pires**         | matheusconrado@alu.ufc.br     |
| 535718     | **Victor Emanuel de Sousa Costa** | victorwmanuel.costa@alu.ufc.br |

---

## 🛠 Technologies

- **Language:** Python 3.12+
- **Web framework:** FastAPI
- **ORM / Persistence:** SQLModel (Pydantic + SQLAlchemy)
- **Package manager:** uv
- **Database migrations:** Alembic
- **Databases:**
  - SQLite (local development)
  - PostgreSQL (production/cloud, e.g. Supabase or Neon)

---

## 🏛 Architecture and Data Model

The project follows a modular architecture. The system is designed to manage resource allocation and task tracking.

```mermaid
classDiagram
    direction LR
    class Project {
        id_project: int
        name_project: str
        description_project: str
    }
    class Task {
        id_task: int
        name_task: str
        description_task: str
        priority: str
        due_date: date_type
    }
    class User {
        id_user: int
        name_user: str
        email_user: str
    }
    class TaskStatus {
        id_task_status: int
        name_task_status: str
    }

    Project "1" *-- "*" Task
    TaskStatus "1" -- "*" Task
    User "*" -- "*" Project
```

### Main Entities

1. **Project:** Represents an organization's projects.
2. **Task:** A unit of work associated with a project.
3. **User:** A person who works on projects.
4. **Task Status:** Defines the workflow (e.g., Pending, In Progress, Completed).

### Implemented Relationships

- **One-to-many (1:N):**
  - A **Project** can have multiple **Tasks**.
  - A **Task Status** can be associated with multiple **Tasks**.
- **Many-to-many (N:N):**
  - **Projects** and **Users**: a user can belong to multiple projects, and a project can have multiple users. This relationship is implemented through an association table.

---

## 🚀 Running the Project

This project uses **uv** for package management, providing a fast and consistent development environment.

### 1. Prerequisites

Make sure `uv` is installed. One installation option is:

```bash
pip install uv
```

### 2. Installation and Virtual Environment

Clone the repository and synchronize the dependencies:

```bash
git clone <repository-url>
cd <project-directory>
uv sync
```

This automatically creates the virtual environment (`.venv`) and installs the dependencies listed in `pyproject.toml`.

### 3. Database Configuration (`.env`)

Create a `.env` file in the project root and set the connection string for the database you want to use.

Example `.env` file:

```ini
# Database configuration
# Uncomment ONLY the line for the database you want to use.

# Option 1: SQLite (local; the database file will be created in the project root)
DATABASE_URL="sqlite:///database.db"

# Option 2: PostgreSQL (cloud; e.g. Supabase or Neon)
# DATABASE_URL="postgresql://username:password@host:port/database_name"
```

### 4. Database Migrations (Alembic)

Run the migrations to create the tables in the selected database:

```bash
uv run alembic upgrade head
```

### 5. Starting the API

Start the development server with:

```bash
uv run fastapi dev main.py
```

Open the interactive API documentation at **[http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs)**.

---

## 🔍 Implemented Features and Queries

The API implements the complex queries required by the project specification.

### Basic Operations (CRUD)

- Full CRUD operations for `Projects`, `Tasks`, `Users`, and `Task Statuses`.

### Additional Routes

- Partial search for projects by project name and description.
- Partial search by name and description.
- Search by task due date.
- Search by task priority.
- Search for overdue tasks.

---

## 📂 Project Structure

```plain
.
├── alembic.ini
├── database.py
├── divisao_tarefas.txt
├── main.py
├── migrations/
│   ├── env.py
│   ├── README
│   ├── script.py.mako
│   └── versions/
├── models/
│   ├── __init__.py
│   ├── project.py
│   ├── project_user.py
│   ├── task.py
│   ├── task_status.py
│   └── user.py
├── pyproject.toml
├── README.md
├── routes/
│   ├── home.py
│   ├── project.py
│   ├── task_status.py
│   └── user.py
├── seed.py
├── temp.py
└── uv.lock
```

---

## ✅ Project Checklist

- [x] Dependency management with `uv` (`pyproject.toml` and `uv.lock`).
- [x] SQLite and PostgreSQL support through `.env` configuration.
- [x] Alembic database migrations.
- [x] At least three entities (Project, Task, User, and Task Status).
- [x] One-to-many and many-to-many relationships.
- [x] Exception handling with `HTTPException`.
- [x] Seed script for initial data.
- [x] `divisao_tarefas.txt` included in the repository.

---

### Note

The `.venv` directory is **not** included in the repository. Run `uv sync` to recreate the environment and install the project dependencies.
