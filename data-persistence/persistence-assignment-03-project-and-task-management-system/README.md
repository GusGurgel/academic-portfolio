# Project and Task Management System

This repository contains the final project for the **Persistence** course, taught at the Federal University of Ceará (UFC).

The goal is to develop a robust API using **FastAPI** and **Beanie (MongoDB)**, demonstrating knowledge of data modeling and complex queries.

## 👥 Team

| Student ID | Name                              | Email                         |
| :--------: | :-------------------------------- | :---------------------------- |
|  539226    | **Gustavo Gurgel Medeiros**       | gusgurgel@alu.ufc.br          |
|  536536    | **Matheus Conrado Pires**         | matheusconrado@alu.ufc.br     |
|  535718    | **Victor Emanuel de Sousa Costa** | victorwmanuel.costa@alu.ufc.br |

---

## 🛠 Technologies

- **Language:** Python 3.12+
- **Web Framework:** FastAPI
- **ODM / Persistence:** Beanie (MongoDB)
- **Dependency Manager:** uv

---

### Main Documents

1. **Project:** Represents the organization's projects.
2. **Task:** Work items associated with a project.
3. **User:** People who work on the projects.
4. **Task Status:** Defines the workflow (e.g., Pending, In Progress, Completed).

---

## 🚀 Running the Project

This project uses **uv** for package management, ensuring speed and consistency.

### 1. Prerequisites

Make sure `uv` is installed:

```bash
pip install uv
```

### 2. Installation and Virtual Environment

Clone the repository and synchronize the dependencies:

```bash
git clone <your-repository-url>
cd <folder-name>
uv sync
```

This will automatically create the virtual environment (`.venv`) and install all dependencies listed in `pyproject.toml`.

### 3. Running the API

Start the development server with:

```bash
uv run fastapi dev main.py
```

Open the interactive API documentation at **[http://127.0.0.1:8000/docs](http://127.0.0.1:8000/docs)**.

---
