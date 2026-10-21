import UPDClient from "./udp_client.js"
import Message from "../models/message.js"
import Account from "../models/account.js"
import { REQUISITION_RETRIES } from "../configs.js"
import { ExceptionFromJSON, TimeoutException } from "../models/exceptions.js"

export default class ProxyBank {
    constructor() {
        this.upd_client =  new UPDClient()
        this.global_id = 0
    }

    // async sleep(s) {
    //     return new Promise(resolve => setTimeout(resolve, s*1000));
    // }

    get_id() {
        this.global_id += 1
        return this.global_id
    }

    async do_operation(method_id, req_arguments) {
        const message = new Message(0, this.get_id(), "Bank", method_id, req_arguments)

        let trys = 0
        while (trys < REQUISITION_RETRIES){
            this.upd_client.sendResponse(message.toJson())
            let retMessage = null

            try{
                retMessage = (await this.upd_client.getResponse()).msg
                retMessage = JSON.parse(retMessage)
                if (retMessage.id != message.id) {
                    continue
                }
                if (retMessage.error) {
                    throw ExceptionFromJSON(retMessage.arguments)
                }

                return retMessage.arguments
            } catch (exception) {
                if (retMessage.error) {
                    throw ExceptionFromJSON(retMessage.arguments)
                } else if (exception instanceof TimeoutException) {
                    console.log(`Requisition timeout try:${trys}`)
                    trys += 1
                } else {
                    throw Error(`Error getting server message: ${exception.message} `)
                }
            }
        }
    }

    async createAccount(res_account_to_create) {
        const res_arguments = await this.do_operation("createAccount", res_account_to_create.toJson())

        res_account_to_create = Account.fromJson(res_arguments)
        return res_account_to_create
    }

    async loginAccount(account_with_credentials) {
        const res_arguments = await this.do_operation("loginAccount", account_with_credentials.toJson())

        const res_login_account = Account.fromJson(res_arguments)
        return res_login_account
    }

    async deposit(account_with_credentials, amount) {
        let req_arguments = account_with_credentials.toJson()
        req_arguments = JSON.parse(req_arguments) 
        req_arguments["amount"] = amount
        
        const res_arguments = await this.do_operation("deposit", JSON.stringify(req_arguments))

        const res_account_with_credentials = Account.fromJson(res_arguments)
        return res_account_with_credentials
    }
    
    async deposit(account_with_credentials, amount) {
        let req_arguments = account_with_credentials.toJson()
        req_arguments = JSON.parse(req_arguments) 
        req_arguments["amount"] = amount
        
        const res_arguments = await this.do_operation("deposit", JSON.stringify(req_arguments))

        const res_account_with_credentials = Account.fromJson(res_arguments)
        return res_account_with_credentials
    }

    async transfer(account_with_credentials, receiver_email, amount) {
        let req_arguments = account_with_credentials.toJson()
        req_arguments = JSON.parse(req_arguments) 
        req_arguments["amount"] = amount
        req_arguments["receiver_email"] = receiver_email
        
        const res_arguments = await this.do_operation("transfer", JSON.stringify(req_arguments))

        const res_account_with_credentials = Account.fromJson(res_arguments)
        return res_account_with_credentials
    }

    close() {
        this.upd_client.close()
    }
}

const proxyBank = new ProxyBank()

proxyBank.close()