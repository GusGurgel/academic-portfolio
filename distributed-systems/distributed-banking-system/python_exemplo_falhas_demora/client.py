from bank_client import *
from models.account import Account

proxyBank = ProxyBank(verbose=True)

gurgelAccount = Account("gus@email.com", "Gurgel", 0, "123")

try:
    gurgelAccount = proxyBank.createAccount(gurgelAccount)
except:
    pass

gurgelAccount = proxyBank.deposit(gurgelAccount, 1000)

print(gurgelAccount)
