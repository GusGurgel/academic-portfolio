from ..models.exceptions import *
import json


class Account:
    def __init__(self, email, name=None, balance=0, password=None):
        if balance != None and balance < 0:
            raise InvalidAmountException("Initial balance cannot be negative.")
        self.email = email
        self.name = name
        self.password = password
        self.balance = balance

    def deposit(self, amount):
        if amount <= 0:
            raise InvalidAmountException("Deposit amount must be positive.")
        self.balance += amount

    def withdraw(self, amount):
        if amount <= 0:
            raise InvalidAmountException("Withdrawal amount must be positive.")
        if amount > self.balance:
            raise InsufficientFundsException("Insufficient funds.")
        self.balance -= amount

    @staticmethod
    def from_json(json_str):
        data = json.loads(json_str)
        return Account(
            data["email"],
            data["name"] if "name" in data else None,
            data["balance"] if "balance" in data else 0,
            data["password"] if "password" in data else None,
        )

    def to_json(self):
        return json.dumps(
            {
                "email": self.email,
                "name": self.name,
                "balance": self.balance,
                "password": self.password,
            }
        )

    def __str__(self):
        return f"""---Account---
email: {self.email}, 
name: {self.name}, 
balance: {self.balance},
password: {self.password}
-------------"""
