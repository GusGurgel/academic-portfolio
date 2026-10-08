import httpx
from pprint import pprint


BASE_URL = "http://localhost:8000"


def makeline():
    print("-" * 80)


def criar_aluno(nome: str, nota: float):
    resp = httpx.post(f"{BASE_URL}/alunos", json={"nome": nome, "nota": nota})
    return resp.json()


def pegar_aluno(nome):
    resp = httpx.get(f"{BASE_URL}/alunos/{nome}")
    return resp.json()


def pegar_todos_alunos():
    resp = httpx.get(f"{BASE_URL}/alunos")
    return resp.json()


makeline()
print("Todos os alunos:")
pprint(pegar_todos_alunos())
makeline()
print("GET nota aluno Erick")
pprint(pegar_aluno("Erick"))
makeline()
print("GET nota aluno Andre")
pprint(pegar_aluno("Andre"))
makeline()
print("POST aluno Jefferson")
pprint(criar_aluno("Jefferson", 10))
makeline()
