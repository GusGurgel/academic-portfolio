import ctypes
import pygame
import pygame_gui
from os.path import join
from background import Background
from platform import system

from gui_config import *

import pygame_gui.ui_manager
from pygame_gui.core import ObjectID

from bank_proxy import *

if system() == "Windows":
    ctypes.windll.user32.SetProcessDPIAware()


class Game:
    def __init__(self):
        pygame.init()

        pygame.display.set_caption(WINDOW_TITLE)

        self.display_surface = pygame.display.set_mode(
            (WINDOW_WIDTH, WINDOW_HEIGHT), vsync=1
        )

        self.draw_group = pygame.sprite.Group()
        self.running = True
        self.clock = pygame.Clock()
        self.ui_manager = pygame_gui.UIManager((WINDOW_WIDTH, WINDOW_HEIGHT), join(MAIN_PATH, "ui_theme.json"))
        self.background = Background(join(IMAGE_PATH, "clouds.png"), self.draw_group)

        self.proxy_bank = ProxyBank(verbose=True)

        self.current_page = None
        self.current_account = None
        self.current_action = ACTIONS_BANK[0]
        self.load_login_page()

        self.login_clock = 0
        self.login_timeout = LOGIN_TIMEOUT
        self.counter = 0

    def load_account_page(self):
        self.ui_manager.clear_and_reset()
        self.current_page = "account"
        self.current_action = ACTIONS_BANK[0]

        row_start = 220
        row_jump = 45
        
        # Title Label
        title_label_rect = pygame.Rect((0, 0), (300, 100))
        self.title_label = pygame_gui.elements.UILabel(
            title_label_rect,
            "Account",
            self.ui_manager,
            object_id=ObjectID(object_id="#title"),
            anchors={
                "centerx": "centerx"
            }
        )

        # status_box
        status_box_rect = pygame.Rect((0, 90), (350, 120))
        self.status_box = pygame_gui.elements.UITextBox(
            "",
            status_box_rect, 
            self.ui_manager,
            object_id=ObjectID(object_id="#status-box"),
            anchors={
                "centerx": "centerx"
            }
        )

        # Action Selection
        select_action_rect = pygame.Rect((0, row_start+(0*row_jump)), (200, 40))
        self.select_action = pygame_gui.elements.UIDropDownMenu(
            ACTIONS_BANK,
            START_ACTION_BACK,
            select_action_rect,
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            },
        )

        # Amount
        input_amount_rect = pygame.Rect((0, row_start+(1*row_jump)), (200, 40))
        self.input_amount = pygame_gui.elements.UITextEntryLine(
            input_amount_rect, 
            self.ui_manager,
            placeholder_text="amount",
            anchors={
                'centerx': 'centerx'
            },
        )

        # Email reciver
        input_email_reciver_rect = pygame.Rect((0, row_start+(2*row_jump)), (200, 40))
        self.input_email_reciver = pygame_gui.elements.UITextEntryLine(
            input_email_reciver_rect, 
            self.ui_manager,
            placeholder_text="email reciver",
            anchors={
                'centerx': 'centerx'
            },
        )

        # Button enter
        button_enter_rect = pygame.Rect((0, row_start+(row_jump*3)), (200, 40))
        self.button_enter = pygame_gui.elements.UIButton(
            button_enter_rect,
            "Enter",
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            }
        )
        
        # Button logout
        button_logout_rect = pygame.Rect((0, row_start+(row_jump*4)), (200, 40))
        self.button_logout = pygame_gui.elements.UIButton(
            button_logout_rect,
            "Logout",
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            }
        )
        
        # Error box
        error_box_rect = pygame.Rect((0, row_start+(row_jump*5)), (400, 40))
        self.error_box = pygame_gui.elements.UITextBox(
            "",
            error_box_rect, 
            self.ui_manager,
            object_id=ObjectID(object_id="#error-box"),
            anchors={
                "centerx": "centerx"
            },
            visible=False
        )
    
    def load_register_page(self):
        self.ui_manager.clear_and_reset()

        self.current_page = "register"
        row_start = 170
        row_jump = 45

        # Title Label
        title_label_rect = pygame.Rect((0, 45), (300, 100))
        self.title_label = pygame_gui.elements.UILabel(
            title_label_rect,
            "Register",
            self.ui_manager,
            object_id=ObjectID(object_id="#title"),
            anchors={
                "centerx": "centerx"
            }
        )

        # Email
        input_email_rect = pygame.Rect((0, row_start), (200, 40))
        self.input_email = pygame_gui.elements.UITextEntryLine(
            input_email_rect, 
            self.ui_manager,
            placeholder_text="email",
            anchors={
                'centerx': 'centerx'
            },
        )

    	# Name
        input_password_name = pygame.Rect((0, row_start+(row_jump*1)), (200, 40))
        self.input_name = pygame_gui.elements.UITextEntryLine(
            input_password_name, 
            self.ui_manager,
            initial_text="",
            anchors={
                'centerx': 'centerx'
            },
            placeholder_text="name"
        )

    	# Password
        input_password_rect = pygame.Rect((0, row_start+(row_jump*2)), (200, 40))
        self.input_password = pygame_gui.elements.UITextEntryLine(
            input_password_rect, 
            self.ui_manager,
            initial_text="",
            anchors={
                'centerx': 'centerx'
            },
            placeholder_text="password"
        )
        self.input_password.set_text_hidden(True)

        # Button Register
        button_register_rect = pygame.Rect((0, row_start+(row_jump*3)), (200, 40))
        self.button_register = pygame_gui.elements.UIButton(
            button_register_rect,
            "Register",
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            }
        )

        # Button Login
        button_login_rect = pygame.Rect((0, row_start+(row_jump*4)), (200, 40))
        self.button_login = pygame_gui.elements.UIButton(
            button_login_rect,
            "Back",
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            }
        )

        # Error box
        error_box_rect = pygame.Rect((0, row_start+(row_jump*5)), (400, 40))
        self.error_box = pygame_gui.elements.UITextBox(
            "error: teste test teste",
            error_box_rect, 
            self.ui_manager,
            object_id=ObjectID(object_id="#error-box"),
            anchors={
                "centerx": "centerx"
            },
            visible=False
        )

    def load_login_page(self):
        self.ui_manager.clear_and_reset()
        
        self.current_page = "login"
        row_start = 170
        row_jump = 45

        # Title Label
        title_label_rect = pygame.Rect((0, 45), (300, 100))
        self.title_label = pygame_gui.elements.UILabel(
            title_label_rect,
            "Login",
            self.ui_manager,
            object_id=ObjectID(object_id="#title"),
            anchors={
                "centerx": "centerx"
            }
        )

        # Email
        input_email_rect = pygame.Rect((0, row_start+(row_jump*0)), (200, 40))
        self.input_email = pygame_gui.elements.UITextEntryLine(
            input_email_rect, 
            self.ui_manager,
            placeholder_text="email",
            anchors={
                'centerx': 'centerx'
            },
        )

    	# Password
        input_password_rect = pygame.Rect((0, row_start+(row_jump*1)), (200, 40))
        self.input_password = pygame_gui.elements.UITextEntryLine(
            input_password_rect, 
            self.ui_manager,
            initial_text="",
            anchors={
                'centerx': 'centerx'
            },
            placeholder_text="password"
        )
        self.input_password.set_text_hidden(True)

        # Button Login
        button_login_rect = pygame.Rect((0, row_start+(row_jump*2)), (200, 40))
        self.button_login = pygame_gui.elements.UIButton(
            button_login_rect,
            "Login",
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            }
        )

        # Button Register
        button_register_rect = pygame.Rect((0, row_start+(row_jump*3)), (200, 40))
        self.button_register = pygame_gui.elements.UIButton(
            button_register_rect,
            "Register",
            self.ui_manager,
            anchors={
                'centerx': 'centerx'
            }
        )

        # Error box
        error_box_rect = pygame.Rect((0, row_start+(row_jump*4)), (400, 40))
        self.error_box = pygame_gui.elements.UITextBox(
            "error: teste test teste",
            error_box_rect, 
            self.ui_manager,
            object_id=ObjectID(object_id="#error-box"),
            anchors={
                "centerx": "centerx"
            },
            visible=False
        )
    
    def handle_register(self):
        email_user = self.input_email.get_text()
        password_user = self.input_password.get_text()
        name_user = self.input_name.get_text()
        account = Account(email_user, name_user, 0, password_user)
        try: 
            res_account = self.proxy_bank.createAccount(account)
            self.handle_success_login(res_account)
        except Exception as e:
            text = f"""<b>Error: </b> <font color=#dc3545>{e}</font>"""
            self.error_box.set_text(text)
            self.error_box.visible = 1
    
    def handle_success_login(self, account):
        self.current_account = account
        self.load_account_page()
        self.update_status()

    def handle_login(self):
        email_user = self.input_email.get_text()
        password_user = self.input_password.get_text()
        account = Account(email_user, None, 0, password_user)
        try: 
            res_account = self.proxy_bank.loginAccount(account)
            self.handle_success_login(res_account)
        except Exception as e:
            text = f"""<b>Error: </b> <font color=#dc3545>{e}</font>"""
            self.error_box.set_text(text)
            self.error_box.visible = 1
    
    def handle_enter(self):
        if self.current_action == "deposit":
            try:
                self.current_account = self.proxy_bank.deposit(self.current_account, int(self.input_amount.get_text()))
                self.update_status()
                self.error_box.visible = 0
            except Exception as e:
                text = f"""<b>Error: </b> <font color=#dc3545>{e}</font>"""
                self.error_box.visible = 1
                self.error_box.set_text(text)

        elif self.current_action == "transfer":
            try:
                self.current_account = self.proxy_bank.transfer(self.current_account, self.input_email_reciver.get_text(), int(self.input_amount.get_text()))
                self.update_status()
                self.error_box.visible = 0
            except Exception as e:
                text = f"""<b>Error: </b> <font color=#dc3545>{e}</font>"""
                self.error_box.visible = 1
                self.error_box.set_text(text)

    def ui_events(self, event):
        if event.type == pygame_gui.UI_BUTTON_PRESSED:
            if self.current_page == "login" and event.ui_element == self.button_register :
                self.load_register_page()
            elif self.current_page == "register" and event.ui_element == self.button_login :
                self.load_login_page()
            elif self.current_page == "register" and event.ui_element == self.button_register:
                self.handle_register()
            elif self.current_page == "login" and event.ui_element == self.button_login:
                self.handle_login()
            elif self.current_page == "account" and event.ui_element == self.button_logout:
                self.current_account = None
                self.load_login_page()
            elif self.current_page == "account" and event.ui_element == self.button_enter:
                self.handle_enter()
        if event.type == pygame_gui.UI_DROP_DOWN_MENU_CHANGED:
            if event.ui_element == self.select_action:
                self.current_action = event.text
                

    def events(self):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                self.running = False
            if event.type == pygame.KEYDOWN:
                if event.key in KEYS["quit"]:
                    self.running = False
                elif event.key == pygame.K_SPACE:
                    self.load_login_page()
            self.ui_manager.process_events(event)
            self.ui_events(event)

    def update_status(self):
        if self.current_page != "account" or self.current_account == None:
            return
        
        text = f"""<b>Email</b>: {self.current_account.email}
<b>Name</b>: {self.current_account.name}
<b>Balance</b>: {self.current_account.balance} R$
"""
        self.status_box.set_text(text)

    def update(self, dt):
        self.draw_group.update(dt)
        self.ui_manager.update(dt)
        if self.current_account != None:
            self.login_clock += dt
            if self.login_clock > self.login_timeout:
                self.login_clock = 0
                try:
                    self.current_account = self.proxy_bank.loginAccount(self.current_account)
                    self.update_status()
                    print("pull")
                except:
                    pass

    def draw(self):
        self.display_surface.fill(COLORS["bg"])

        self.draw_group.draw(self.display_surface)
        self.ui_manager.draw_ui(self.display_surface)
        pygame.display.update()

    def start(self):
        while self.running:
            dt = self.clock.tick() / 1000
            self.events()
            self.update(dt)
            self.draw()

        pygame.quit()


if __name__ == "__main__":
    game = Game()

    game.start()