import { getLocalHostIP } from "./utils.js"

export const BUFFER_SIZE = 2048
export const FORMAT = "utf-8"

// Client
export const REQUISITION_TIMEOUT = 0.5
export const REQUISITION_RETRIES = 5

// Server
export const SERVER_PORT = 12000
export const SERVER_IP = await getLocalHostIP()
export const SERVER_ADDR = (SERVER_IP, SERVER_PORT)