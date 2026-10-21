import socket


def format_addr(addr):
    return f"{addr[0]}:{addr[1]}"


def getLocalHostIP():
    return socket.gethostbyname(socket.gethostname())
