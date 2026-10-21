import * as dgram from "node:dgram"
import { Buffer } from "node:buffer"
import { REQUISITION_TIMEOUT, SERVER_IP, SERVER_PORT } from "../configs.js"
import { TimeoutException } from "../models/exceptions.js"


export default class UPDClient {
    constructor(verbose) {
        this.verbose = verbose
        this.socket = dgram.createSocket('udp4')
    }

    sendResponse(_message) {
        const message = Buffer.from(_message)
        this.socket.send(message, SERVER_PORT, SERVER_IP)
    }

    async getResponse() {

        return new Promise((resolve, reject) => {
            const timer = setTimeout(() => {
                reject(new TimeoutException("Timeout: Nenhuma resposta recebida dentro do tempo limite"));
                this.socket.removeAllListeners('message'); // Remover listener para evitar vazamento de memória
            }, REQUISITION_TIMEOUT * 1000);

            this.socket.once('message', (msg, rinfo) => {
                msg = msg.toString()
                resolve({ msg, rinfo });
            });
        });
    }

    close() {
        this.socket.close()
    }
}