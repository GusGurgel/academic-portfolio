import readline from "readline";
import ProxyBank from "./proxy_bank.js";
import Account from "../models/account.js";

const proxyBank = new ProxyBank();

const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

console.log("🚀 CLI do Banco UDP iniciado! Digite um comando (help para ver os comandos disponíveis)");

const showHelp = () => {
    console.log(`
Comandos disponíveis:
    createAccount <email> <senha>                               - Cria uma conta
    login <email> <senha>                                       - Faz login na conta
    deposit <email> <senha> <valor>                             - Deposita um valor na conta
    transfer <email> <senha> <email do destinatario> <valor>    - Transfere um valor
    exit                                                        - Sai do CLI
    `);
};

const processCommand = async (input) => {
    const args = input.trim().split(" ");
    const command = args[0];

    try {
        switch (command) {
            case "createAccount":
                if (args.length !== 4) {
                    console.log("Uso: createAccount <email> <nome> <senha>");
                    break;
                }
                const newAccount = new Account(args[1], args[2], 0, args[3]);
                const createdAccount = await proxyBank.createAccount(newAccount);
                console.log("✅ Conta criada:", createdAccount);
                break;

            case "login":
                if (args.length !== 3) {
                    console.log("Uso: login <email> <senha>");
                    break;
                }
                const loginAccount = new Account(args[1], "blablabla", 0, args[2]);
                const loggedIn = await proxyBank.loginAccount(loginAccount);
                console.log("🔓 Login bem-sucedido:", loggedIn);
                break;

            case "deposit":
                if (args.length !== 4) {
                    console.log("Uso: deposit <email> <senha> <valor>");
                    break;
                }
                const depositAccount = new Account(args[1], "blablabla", 0, args[2]);
                const updatedAccount = await proxyBank.deposit(depositAccount, parseFloat(args[3]));
                console.log("💰 Depósito realizado:", updatedAccount);
                break;

            case "transfer":
                if (args.length !== 5) {
                    console.log("Uso: transfer <email> <senha> <email do destinatario> <valor>");
                    break;
                }
                const senderAccount = new Account(args[1], "blablabla", 0, args[2]);
                const transferredAccount = await proxyBank.transfer(senderAccount, args[3], parseFloat(args[4]));
                console.log("💸 Transferência realizada:", transferredAccount);
                break;

            case "help":
                showHelp();
                break;

            case "exit":
                console.log("👋 Encerrando CLI...");
                proxyBank.close();
                rl.close();
                process.exit(0);
                break;

            default:
                console.log("Comando não reconhecido. Digite 'help' para ver os comandos disponíveis.");
        }
    } catch (error) {
        console.error("❌ Erro:", error.message);
    }
};

rl.on("line", processCommand);
