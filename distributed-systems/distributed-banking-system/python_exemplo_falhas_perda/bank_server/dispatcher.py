from bank_server.bank_skeleton import BankSkeleton
from models.message import Message


class Dispatcher:
    def __init__(self):
        self.skeletons = {"Bank": BankSkeleton()}

    def invoke(self, message: Message) -> str:
        # Get method from skeleton
        method = getattr(self.skeletons[message.obfReference], message.methodId)
        # Call method with arguments and return
        return method(message.arguments)
