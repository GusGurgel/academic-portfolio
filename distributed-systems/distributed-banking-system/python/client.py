from bank_client import *
from models.account import Account

proxyBank = ProxyBank(verbose=True)

gurgelAccount = Account("gus@email.com", "Gurgel", 0, "123")
marioAccount = Account("mar@email.com", "Mario", 0, "123")

gurgelAccount = proxyBank.transfer(gurgelAccount, "mar@email.com", 1000)
marioAccount = proxyBank.loginAccount(marioAccount)


# gurgelAccount = proxyBank.loginAccount(gurgelAccount)


print(gurgelAccount)
print(marioAccount)