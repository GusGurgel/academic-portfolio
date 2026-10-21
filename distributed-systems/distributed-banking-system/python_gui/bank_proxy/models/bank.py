from models.exceptions import *

from models.account import Account


class Bank:
    def __init__(self):
        self.accounts: dict[str, Account] = {}


    def createAccount(self, account_to_create) -> Account:
        """
        Create an account and save it in the bank.

        Can raise the exceptions:
        InvalidAttributeValueException if email, name, balance or password is null
        EmailAlreadyExistsException if already exists a account with the same email
        """

        # Check for null values
        for attribute in ["email", "name", "password", "balance"]:
            if getattr(account_to_create, attribute) == None:
                raise InvalidAttributeValueException(attribute, None)
        # Check for email already used
        if account_to_create.email in self.accounts:
            raise EmailAlreadyExistsException()
        # Save account on bank
        self.accounts[account_to_create.email] = account_to_create
        return account_to_create

    def loginAccount(self, account_with_credentials) -> Account:
        """
        Login to Account to get name and balance updated

        Can raise the exceptions:
        InvalidCredentialsException if email or password don't match with any
        account
        """
        for attribute in ["email", "password"]:
            if getattr(account_with_credentials, attribute) == None:
                raise InvalidCredentialsException("Invalid email or password.")
        account = self.accounts.get(account_with_credentials.email)
        if not account or account.password != account_with_credentials.password:
            raise InvalidCredentialsException("Invalid email or password.")
        return account


    def deposit(self, account_to_deposit, amount) -> Account:
        """
        Deposit a positive amount to a Account

        Can raise the exceptions:
        InvalidCredentialsException if email or password don't match with any
        InvalidAmountException if amount is negative or null
        account
        """

        # Check for negative or null amount
        if amount == None or amount < 0:
            raise InvalidAmountException()
        # Login to account
        self.loginAccount(account_to_deposit)
        # Get account and deposit amount
        account = self.accounts.get(account_to_deposit.email)
        account.balance += amount
        return account


    def transfer(self, account_with_credentials, receiver_email, amount) -> Account:
        """
        Transfer a positive amount to another account

        Can raise the exceptions:
        InvalidCredentialsException if email or password don't match with any
        InvalidAmountException if amount is negative or null account
        InsufficientFundsException if send won't have enough money
        InsufficientFundsException if receiver account not exists 
        SameAccountTransferException if sender email and receiver email are the same
        """

        sender = self.accounts.get(account_with_credentials.email)
        if not sender or sender.password != account_with_credentials.password:
            raise InvalidCredentialsException("Invalid email or password.")
        if account_with_credentials.email == receiver_email:
            raise SameAccountTransferException("Cannot transfer to the same account.")
        receiver = self.accounts.get(receiver_email)
        if not receiver:
            raise AccountNotFoundException("Receiver account not found.")
        if amount <= 0:
            raise InvalidAmountException("Transfer amount must be positive.")
        if sender.balance < amount:
            raise InsufficientFundsException("Insufficient funds.")

        sender.withdraw(amount)
        receiver.deposit(amount)

        return sender
