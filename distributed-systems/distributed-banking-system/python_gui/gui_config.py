import pygame
from os.path import realpath, dirname, join

WINDOW_TITLE = "BankSystem"

WINDOW_WIDTH, WINDOW_HEIGHT = (500, 500)

LOGIN_TIMEOUT = 3.5

MAIN_PATH = realpath(dirname(__file__))
IMAGE_PATH = join(MAIN_PATH, "images")

ACTIONS_BANK = [
    "deposit",
    "transfer"
]

START_ACTION_BACK = ACTIONS_BANK[0]

KEYS = {
    "quit": [pygame.K_q]
}

COLORS = {
    "bg" : "skyblue"
}