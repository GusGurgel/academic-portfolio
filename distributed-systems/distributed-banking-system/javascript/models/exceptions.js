export class TimeoutException extends  Error {
    constructor(message) {
        super(message)
    }
}

export class SerializableException extends Error {
    constructor(message = "Unknown error", code = -1) {
        super(message);
        this.code = code;
    }

    toJson() {
        return JSON.stringify({ code: this.code, message: this.message });
    }

    static fromJson(jsonStr) {
        return new SerializableException();
    }
}

export class InvalidAmountException extends SerializableException {
    constructor() {
        super("Invalid amount", 0);
    }

    static fromJson(jsonStr) {
        return new InvalidAmountException();
    }
}

export class EmailAlreadyExistsException extends SerializableException {
    constructor() {
        super("Email already exists", 1);
    }

    static fromJson(jsonStr) {
        return new EmailAlreadyExistsException();
    }
}

export class InvalidCredentialsException extends SerializableException {
    constructor() {
        super("Invalid credentials", 2);
    }

    static fromJson(jsonStr) {
        return new InvalidCredentialsException();
    }
}

export class AccountNotFoundException extends SerializableException {
    constructor() {
        super("Account not found", 3);
    }

    static fromJson(jsonStr) {
        return new AccountNotFoundException();
    }
}

export class InsufficientFundsException extends SerializableException {
    constructor() {
        super("Insufficient funds", 4);
    }

    static fromJson(jsonStr) {
        return new InsufficientFundsException();
    }
}

export class SameAccountTransferException extends SerializableException {
    constructor() {
        super("Same account transfer not allowed", 5);
    }

    static fromJson(jsonStr) {
        return new SameAccountTransferException();
    }
}

export class InvalidAttributeValueException extends SerializableException {
    constructor(attributeName, attributeValue) {
        super(`Invalid attribute ${attributeName} = ${attributeValue}`, 6);
        this.attributeName = attributeName;
        this.attributeValue = attributeValue;
    }

    static fromJson(jsonStr) {
        const data = JSON.parse(jsonStr);
        return new InvalidAttributeValueException(data.attribute_name, data.attribute_value);
    }

    toJson() {
        return JSON.stringify({
            code: this.code,
            message: this.message,
            attribute_name: this.attributeName,
            attribute_value: this.attributeValue
        });
    }
}

const exceptionsMap = {
    0: InvalidAmountException,
    1: EmailAlreadyExistsException,
    2: InvalidCredentialsException,
    3: AccountNotFoundException,
    4: InsufficientFundsException,
    5: SameAccountTransferException,
    6: InvalidAttributeValueException
};

export function ExceptionFromJSON(jsonStr) {
    const data = JSON.parse(jsonStr);
    if (!("code" in data)) {
        throw new Error("Null exception code");
    }
    if (!(data.code in exceptionsMap)) {
        throw new Error(`Invalid exception code ${data.code}`);
    }
    return exceptionsMap[data.code].fromJson(jsonStr);
}