import socket

from config import *
from utils import *


class UDPClient:
    def __init__(self, verbose=False):
        # Socket Server
        self.verbose = verbose
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((getLocalHostIP(), 0))  # Bind to any address
        self.addr = self.socket.getsockname()
        self.socket.settimeout(REQUISITION_TIMEOUT)

        if self.verbose:
            print(f"[Verbose] UDP Client started on {format_addr(self.addr)}")

    def sendResponse(self, response, addr) -> bool:
        try:
            self.socket.sendto(response.encode(FORMAT), addr)
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
