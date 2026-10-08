from os.path import abspath, dirname, join
from bs4 import BeautifulSoup

# Isso aqui é caminho absoluto para a pasta que contem questao_05.py Coloquei
# para evitar problemas com caminhos relativos
script_abs_path = dirname(abspath(__file__))


# Passado a jogada1 (Jogada do jogador 1) e jogada2 (Jogada do jogador 2)
# retorna se o jogador 1 foi vencedor
def is_jogador_1_winner(jogada1: str, jogada2: str) -> bool:
    if jogada1 == "pedra" and jogada2 == "tesoura":
        return True
    elif jogada1 == "papel" and jogada2 == "pedra":
        return True
    elif jogada1 == "tesoura" and jogada2 == "papel":
        return True
    else:
        # Consideramos empate como uma "não vitória"
        return False


with open(join(script_abs_path, "jogadas.html"), encoding="utf-8", mode="r") as file:
    soup = BeautifulSoup(file, "html.parser")

    if soup:
        jogadas = soup.find_all("td")

        wins_jogador_1 = 0

        for i in range(1, len(jogadas), 2):
            jogada1 = jogadas[i - 1].get_text()
            jogada2 = jogadas[i].get_text()
            if is_jogador_1_winner(jogada1, jogada2):
                wins_jogador_1 += 1

        print("Número de vitórias do jogador 1:", wins_jogador_1)
