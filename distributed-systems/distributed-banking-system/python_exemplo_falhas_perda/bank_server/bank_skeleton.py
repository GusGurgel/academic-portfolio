from models.bank import Bank
from models.account import Account
from models.exceptions import *


class BankSkeleton:
    def __init__(self):
        # Bank servant
        self.bank = Bank()

    def createAccount(self, arguments) -> str:
        account = Account.from_json(arguments)
        account = self.bank.createAccount(account)
        return account.to_json()

    def loginAccount(self, arguments) -> str:
        account = Account.from_json(arguments)
        account = self.bank.loginAccount(account)
        return account.to_json()

    def deposit(self, arguments) -> str:
        account = Account.from_json(arguments)
        amount = json.loads(arguments).get("amount")
        account = self.bank.deposit(account, amount)
        return account.to_json()
    
    def transfer(self, arguments):
        account = Account.from_json(arguments)
        amount = json.loads(arguments).get("amount")
        receiver_email = json.loads(arguments).get("receiver_email")
        account = self.bank.transfer(account, receiver_email, amount)
        return account.to_json()
