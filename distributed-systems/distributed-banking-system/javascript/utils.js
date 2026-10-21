import dns from "node:dns"
import os from "node:os"

const options = { family: 4 };

export function getLocalHostIP() {
    return new Promise((resolve, reject) => {
        dns.lookup(os.hostname(), options, (error, address) => {
            if (error) {
                reject(error);
            } else {
                resolve(address);
            }
        });
    });
}
