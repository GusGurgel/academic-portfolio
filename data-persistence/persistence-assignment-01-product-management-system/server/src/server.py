# Aluno: Gustavo Gurgel Medeiros - 539226
#
# Primeiro trabalho da disciplina de persistência 2025.2
#
# Para rodar o programa utilize: `uvicorn server:app --reload --reload-exclude "*.csv"`


import asyncio
from math import isnan
from os.path import abspath, dirname, exists, join

import numpy as np
import pandas as pd
from fastapi import FastAPI, HTTPException
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel

app = FastAPI()
lock = asyncio.Lock()

app.add_middleware(
    CORSMiddleware, allow_origins=["*"], allow_methods=["*"], allow_headers=["*"]
)

script_abs_path = dirname(abspath(__file__))
csv_produtos_data_path = join(script_abs_path, "data.csv")

# ----------------------------------------
# | Funções utilitárias                  |
# ----------------------------------------

_global_id = 0


def get_id() -> int:
    """
    Returns a unique id
    """
    global _global_id
    _global_id += 1

    return _global_id


# Carrega os dados salvos em memória
def load_produtos_csv_data() -> pd.DataFrame:
    produtos_df = pd.DataFrame(
        {
            "id": pd.Series(dtype="int"),  # Identificador único do produto
            "nome": pd.Series(dtype="str"),  # Nome do produto
            "categoria": pd.Series(dtype="str"),  # Categoria do produto
            "preco": pd.Series(dtype="float"),  # Preço do produto
        }
    )

    if not exists(csv_produtos_data_path):
        produtos_df.to_csv(csv_produtos_data_path, index=False)
    else:
        produtos_df = pd.read_csv(csv_produtos_data_path)

    return produtos_df


# Persiste os dados que estão em produtos_df em um arquivo csv
def sync_produtos_csv_data() -> None:
    produtos_df.to_csv(csv_produtos_data_path, index=False)


produtos_df = load_produtos_csv_data()

# Configuring global id
max_id = produtos_df["id"].max()
if isnan(max_id):
    _global_id = 0
else:
    _global_id = int((produtos_df["id"].max()))


# ----------------------------------------
# | Modelos                              |
# ----------------------------------------


class Produto(BaseModel):
    nome: str
    categoria: str
    preco: float


# ----------------------------------------
# | Rotas de produto (Novas rotas)       |
# ----------------------------------------


@app.get("/produtos/max-price", tags=["Produtos (Novo)"])
def get_max_price_produtos():
    if produtos_df.empty:
        raise HTTPException(status_code=404, detail=f"Nenhum produto salvo na banco.")

    produto = produtos_df.loc[produtos_df["preco"].idxmax()]

    return {"message": "Produto encontrado.", "data": produto.to_dict()}


@app.get("/produtos/min-price", tags=["Produtos (Novo)"])
def get_min_price_produtos():
    if produtos_df.empty:
        raise HTTPException(status_code=404, detail=f"Nenhum produto salvo na banco.")

    produto = produtos_df.loc[produtos_df["preco"].idxmin()]

    return {"message": "Produto encontrado.", "data": produto.to_dict()}


@app.get("/produtos/mean", tags=["Produtos (Novo)"])
def get_mean_price_produtos():
    if produtos_df.empty:
        raise HTTPException(status_code=404, detail=f"Nenhum produto salvo na banco.")

    return {
        "message": "Retornando produtos com preço maior que a média.",
        "data": produtos_df["preco"].mean(),
    }


@app.get("/produtos/higher-than-mean", tags=["Produtos (Novo)"])
def get_higher_then_mean_price_produtos():
    if produtos_df.empty:
        raise HTTPException(status_code=404, detail=f"Nenhum produto salvo na banco.")

    produtos = produtos_df[produtos_df["preco"] >= produtos_df["preco"].mean()]

    return {
        "message": "Retornando produtos com preço menor que a média.",
        "data": produtos.to_dict(orient="records"),
    }


@app.get("/produtos/less-than-mean", tags=["Produtos (Novo)"])
def get_higher_less_mean_price_produtos():
    if produtos_df.empty:
        raise HTTPException(status_code=404, detail=f"Nenhum produto salvo na banco.")

    produtos = produtos_df[produtos_df["preco"] < produtos_df["preco"].mean()]

    return {"message": "Média calculada.", "data": produtos.to_dict(orient="records")}


# ----------------------------------------
# | Rotas de produtos                    |
# ----------------------------------------


@app.post("/produtos", tags=["Produtos"])
async def post_produto(produto: Produto):
    async with lock:
        global produtos_df

        novo_produto = {
            "id": get_id(),
            "nome": produto.nome,
            "categoria": produto.categoria,
            "preco": produto.preco,
        }

        produtos_df = pd.concat(
            [produtos_df, pd.DataFrame([novo_produto])], ignore_index=True
        )

        sync_produtos_csv_data()  # Salvar em memória

        return {"message": "Produto salvo com sucesso.", "data": novo_produto}


@app.get("/produtos", tags=["Produtos"])
def get_produtos():
    return {
        "message": "Retornando todos os produtos.",
        "data": produtos_df.to_dict(orient="records"),
    }


@app.get("/produtos/{id}", tags=["Produtos"])
def get_produtos_by_id(id: int):
    produto: pd.DataFrame = produtos_df.loc[produtos_df["id"] == id]

    if produto.empty:
        raise HTTPException(
            status_code=404, detail=f"Produto como id ({id}) não encontrado."
        )

    return {
        "message": "Produto encontrado.",
        "data": produto.to_dict(orient="records")[0],
    }


@app.delete("/produtos/{id}", tags=["Produtos"])
async def delete_produtos_by_id(id: int):
    async with lock:
        global produtos_df

        produto_index = produtos_df.index[produtos_df["id"] == id]

        if produto_index.empty:
            raise HTTPException(
                status_code=404, detail=f"Produto como id ({id}) não encontrado."
            )

        produtos_df = produtos_df.drop(produto_index).reset_index(drop=True)

        sync_produtos_csv_data()  # Salvar em memória

        return {
            "message": f"Produto com id ({id}) deletado.",
        }


@app.put("/produtos/{id}", tags=["Produtos"])
async def put_product_by_id(id: int, produto: Produto):
    async with lock:
        global produtos_df
        produto_index = produtos_df.index[produtos_df["id"] == id]
        if produto_index.empty:
            raise HTTPException(
                status_code=404, detail=f"Produto como id ({id}) não encontrado."
            )

        old_product = produtos_df.loc[produto_index]

        produtos_df.loc[produto_index, ["nome", "categoria", "preco"]] = [
            produto.nome,
            produto.categoria,
            produto.preco,
        ]

        sync_produtos_csv_data()  # Salvar em memória

        return {
            "message": f"Produto com id={id} editado.",
            "data": {
                "new_product": produtos_df.loc[produto_index].to_dict(orient="records")[
                    0
                ],
                "old_product": old_product.to_dict(orient="records")[0],
            },
        }


# ----------------------------------------
# | Rotas de debugs                      |
# ----------------------------------------


@app.get("/ping", tags=["Debug"])
def ping():
    return {"message": "pong"}
