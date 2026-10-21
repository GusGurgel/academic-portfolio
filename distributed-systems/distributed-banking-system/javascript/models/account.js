import { InvalidAmountException, InsufficientFundsException } from "./exceptions.js"

export default class Account {
    constructor(email, name = null, balance = 0, password = null) {
        if (balance !== null && balance < 0) {
            throw new InvalidAmountException("Initial balance cannot be negative.");
        }
        this.email = email;
        this.name = name;
        this.password = password;
        this.balance = balance;
    }

    deposit(amount) {
        if (amount <= 0) {
            throw new InvalidAmountException("Deposit amount must be positive.");
        }
        this.balance += amount;
    }

    withdraw(amount) {
        if (amount <= 0) {
            throw new InvalidAmountException("Withdrawal amount must be positive.");
        }
        if (amount > this.balance) {
            throw new InsufficientFundsException("Insufficient funds.");
        }
        this.balance -= amount;
    }

    static fromJson(jsonStr) {
        const data = JSON.parse(jsonStr);
        return new Account(
            data.email,
            data.name || null,
            data.balance || 0,
            data.password || null
        );
    }

    toJson() {
        return JSON.stringify({
            email: this.email,
            name: this.name,
            balance: this.balance,
            password: this.password
        });
    }

    toString() {
        return `---Account---\nemail: ${this.email}, \nname: ${this.name}, \nbalance: ${this.balance},\npassword: ${this.password}\n-------------`;
    }
}