import os
from dotenv import load_dotenv

load_dotenv()

# Database configuration
PG_HOST = os.getenv("PG_HOST", "localhost")
PG_PORT = os.getenv("PG_PORT", "5432")
PG_USER = os.getenv("PG_USER", "postgres")
PG_PASSWORD = os.getenv("PG_PASSWORD", "password")
PG_DATABASE = os.getenv("PG_DATABASE", "forum")

# Server configuration
PORT = int(os.getenv("PORT", 8000))

# Database URL
DATABASE_URL = f"postgresql://{PG_USER}:{PG_PASSWORD}@{PG_HOST}:{PG_PORT}/{PG_DATABASE}"

# Anonymous nicknames
SUBSTANTIVOS = [
    "Gato", "Cachorro", "Pássaro", "Peixe", "Tigre", "Leão", "Urso", "Lobo",
    "Águia", "Falcão", "Cobra", "Tartaruga", "Coelho", "Raposa", "Panda",
    "Dragão", "Unicórnio", "Fenix", "Ninja", "Mago", "Guerreiro", "Cavaleiro",
    "Pirata", "Robô", "Alien", "Fantasma", "Zumbi", "Vampiro", "Anjo", "Demônio"
]

ADJETIVOS = [
    "Corajoso", "Sábio", "Rápido", "Forte", "Inteligente", "Misterioso", "Silencioso",
    "Feroz", "Gentil", "Calmo", "Selvagem", "Astuto", "Brilhante", "Escuro", "Dourado",
    "Prateado", "Vermelho", "Azul", "Verde", "Roxo", "Místico", "Lendário", "Épico",
    "Poderoso", "Veloz", "Invisível", "Mágico", "Sombrio", "Radiante", "Etéreo"
]