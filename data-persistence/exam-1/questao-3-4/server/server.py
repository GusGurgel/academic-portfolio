# Run with
# uvicorn server:app --reload
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel
import pandas as pd
import asyncio

app = FastAPI()

lock = asyncio.Lock()


class Aluno(BaseModel):
    nome: str
    nota: float


# Alguns alunos aleatórios pre-definidos para colocar no DataFrame
predefined_alunos = [
    {"nome": "João", "nota": 5.5},
    {"nome": "Pedro", "nota": 4.7},
    {"nome": "Kaic", "nota": 8.8},
    {"nome": "Erick", "nota": 9.9},
    {"nome": "Wescley", "nota": 4.4},
    {"nome": "Jorge", "nota": 3.1},
    {"nome": "Eduardo", "nota": 2.2},
]

df_alunos = pd.DataFrame(predefined_alunos)


@app.post("/alunos")
async def post_alunos(aluno: Aluno):
    global df_alunos

    aluno_exists = df_alunos[df_alunos["nome"] == aluno.nome]

    # Usa o lock para operação de escrita ou atualização
    async with lock:
        new_aluno = {"nome": aluno.nome, "nota": aluno.nota}
        if aluno_exists.empty:
            # Adiciona novo aluno
            df_alunos = pd.concat(
                [df_alunos, pd.DataFrame([new_aluno])], ignore_index=True
            )
            return {"data": new_aluno, "message": "Novo aluno cadastrado com sucesso."}
        else:
            index_aluno = df_alunos.index[df_alunos["nome"] == aluno.nome]
            old_aluno = df_alunos.loc[index_aluno][["nome", "nota"]]
            df_alunos.loc[index_aluno, ["nome", "nota"]] = [aluno.nome, aluno.nota]
            return {
                "data": {
                    "new_aluno": new_aluno,
                    "old_aluno": old_aluno.to_dict(orient="records")[0],
                },
                "message": "O aluno já existia, aluno atualizado com sucesso.",
            }


@app.get("/alunos/{nome}")
def get_aluno(nome: str):
    aluno = df_alunos[df_alunos["nome"] == nome]

    if aluno.empty:
        raise HTTPException(
            status_code=404, detail=f"Aluno com nome '{nome}' não foi encontrado"
        )
    else:
        return {"nota": aluno.iloc[0].nota}


@app.get("/alunos")
def get_alunos():
    return {"data": df_alunos.to_dict(orient="records")}
