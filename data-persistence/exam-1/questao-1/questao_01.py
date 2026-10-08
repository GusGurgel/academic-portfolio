from os.path import abspath, dirname, join
from statistics import mean

# Isso aqui é caminho absoluto para a pasta que contem questao_01.py Coloquei
# para evitar problemas com caminhos relativos
script_abs_path = dirname(abspath(__file__))

with open(join(script_abs_path, "dados_alunos.txt"), "r") as file:
    file_str = file.read()

    lines = file_str.split("\n")

    alunos = []
    notas = []  # usado para calcular a média

    for line in lines:
        values = line.split("#")

        if len(values) == 3:
            alunos.append(
                {"nome": values[0], "curso": values[1], "nota": float(values[2])}
            )
            notas.append(float(values[2]))

    print("Média da turma:", mean(notas))
    maior_nota = max(notas)
    aluno_maior_nota = list(filter(lambda v: v["nota"] == maior_nota, alunos))[0]
    print(f"Maior nota: {maior_nota} ({aluno_maior_nota["nome"]})")

    menor_nota = min(notas)
    aluno_menor_nota = list(filter(lambda v: v["nota"] == menor_nota, alunos))[0]
    print(f"Menor nota: {menor_nota} ({aluno_menor_nota["nome"]})")
