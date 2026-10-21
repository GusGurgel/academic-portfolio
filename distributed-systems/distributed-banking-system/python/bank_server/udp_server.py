from utils import *
from config import *
from bank_server.dispatcher import Dispatcher
from time import sleep

from models.message import Message
from models.exceptions import *


import socket


class UDPServer:
    def __init__(self, verbose=False):
        # Internal vars
        self.requisitions = {}
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind(SERVER_ADDR)
        self.addr = SERVER_ADDR
        self.dispatcher = Dispatcher()
        self.socket.settimeout(None)

        self.verbose = verbose

        if self.verbose:
            print(f"[Verbose] UDP Server started on {format_addr(SERVER_ADDR)}")

    def run(self):
        while True:
            # Get message
            try:
                message, addr = self.getResponse()
            # When the client send a request then close
            except ConnectionResetError as e:
                continue
            

            message = Message.from_json(message)

            if self.verbose:
                print(message)

            if (addr, message.id) in self.requisitions:
                # Send response
                print(self.requisitions[(addr, message.id)])
                self.sendResponse(self.requisitions[(addr, message.id)], addr)
            else:
                # Process message
                try:
                    response = self.dispatcher.invoke(message)
                    # Create message
                    message = Message(
                        1,
                        message.id,
                        message.obfReference,
                        message.methodId,
                        response,
                        False,
                    )
                # In case of Serializable Exception
                except SerializableException as e:
                    message = Message(
                        1,
                        message.id,
                        message.obfReference,
                        message.methodId,
                        e.to_json(),
                        True,
                    )
                # Default exception in case of a unknown error
                except Exception as e:
                    message = Message(
                        1,
                        message.id,
                        message.obfReference,
                        message.methodId,
                        SerializableException().to_json(),
                        True,
                    )
                finally:
                    # Save message
                    self.requisitions[(addr, message.id)] = message.to_json()

                    if self.verbose:
                        print(message)

                    # Send response
                    self.sendResponse(message.to_json(), addr)

    def sendResponse(self, reponse, addr) -> bool:
        try:
            self.socket.sendto(reponse.encode(FORMAT), addr)
            return True
        except:
            return False

    def getResponse(self):
        res, addr = self.socket.recvfrom(BUFFER_SIZE)
        return res.decode(FORMAT), addr

    def close(self):
        self.socket.close()

        if self.verbose:
            print(f"[Verbose] End connection")
