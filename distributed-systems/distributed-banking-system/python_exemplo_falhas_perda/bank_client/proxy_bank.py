import json

from config import *

from .udp_client import UDPClient

from models.exceptions import *
from models.message import Message
from models.account import Account


class ProxyBank:
    def __init__(self, verbose=True):
        self.udp_client = UDPClient(verbose)
        self.global_id = 0

    def get_id(self):
        self.global_id += 1
        return self.global_id

    def do_operation(self, method_id: str, arguments: str) -> str:
        message = Message(0, self.get_id(), "Bank", method_id, arguments)

        trys = 1
        while trys <= REQUISITION_RETRIES:
            self.udp_client.sendResponse(message.to_json(), SERVER_ADDR)

            try:
                res, _ = self.udp_client.getResponse()
                res_message = Message.from_json(res)
                if res_message.id != message.id:
                    print(f"(Message id={message.id}) try: {trys}")
                    trys += 1
                    continue
                if res_message.error:
                    print(f"(Message id={message.id}) success ✅", trys)
                    raise ExceptionFromJSON(res_message.arguments)
                print(f"(Message id={message.id}) success ✅", trys)
                return res_message.arguments
            except TimeoutError as e:
                print(f"(Message id={message.id}) try: {trys}")
                trys += 1

    def createAccount(self, account_to_create: Account) -> Account:
        arguments = self.do_operation("createAccount", account_to_create.to_json())

        account_to_create = Account.from_json(arguments)
        return account_to_create

    def loginAccount(self, account_with_credentials: Account) -> Account:
        arguments = self.do_operation("loginAccount", account_with_credentials.to_json())

        account_with_credentials = Account.from_json(arguments)
        return account_with_credentials

    def deposit(self, account_to_deposit: Account, amount: int) -> Account:
        arguments = account_to_deposit.to_json()
        arguments = json.loads(arguments)
        arguments["amount"] = amount
        arguments = self.do_operation("deposit", json.dumps(arguments))

        print(arguments)
        account_to_deposit = Account.from_json(arguments)
        return account_to_deposit
    
    def transfer(self, account_with_credentials: Account, receiver_email : str, amount: int) -> Account:
        arguments = account_with_credentials.to_json()
        arguments = json.loads(arguments)
        arguments["amount"] = amount
        arguments["receiver_email"] = receiver_email
        arguments = self.do_operation("transfer", json.dumps(arguments))

        account = Account.from_json(arguments)
        return account

    def close(self):
        self.udp_client.close()
