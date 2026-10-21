import pygame
from gui_config import *
from math import ceil

class Background(pygame.sprite.Sprite):
    def __init__(self, surface_path : str, groups):
        super().__init__(groups)

        bg_surface = pygame.image.load(surface_path).convert()
        bg_surface_rect = bg_surface.get_frect()
        self.image = pygame.Surface((WINDOW_WIDTH, WINDOW_HEIGHT))
        x = ceil(WINDOW_WIDTH / bg_surface_rect.width)
        y = ceil(WINDOW_HEIGHT / bg_surface_rect.height)

        for i in range(0, x):
            for j in range(0, y):
                self.image.blit(bg_surface, (i * bg_surface_rect.width, j * bg_surface_rect.height))

        self.rect = self.image.get_frect()
    
    def update(self, dt):
        pass