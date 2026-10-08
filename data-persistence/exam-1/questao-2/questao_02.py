import pandas as pd

dados = [12000, 17500, 14300, 16000, 19500]
nomes = ["Luca Brasi", "Peter Clemenza", "Sal Tessio", "Tom Hagen", "Michael Corleone"]

week_employees_balance = pd.Series(dados, index=nomes)

print("O total arrecadado na semana:", week_employees_balance.sum())
print("A média das receitas:", week_employees_balance.mean())
print("O nome do associado que mais arrecadou:", week_employees_balance.idxmax())
print("Associados que arrecadaram acima da média:")
print(
    week_employees_balance[
        week_employees_balance > week_employees_balance.mean()
    ].to_string(dtype=False),
)
