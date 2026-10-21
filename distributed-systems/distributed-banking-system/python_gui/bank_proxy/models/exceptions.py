import json

"""
Exception that can be serialized in JSON format
"""


class SerializableException(Exception):
    def __init__(self, *args):
        # Default code set to -1 as Unknown errorn
        self.code = -1
        self.message = "Unknown error"
        super().__init__(*args)

    def to_json(self) -> str:
        return json.dumps({"code": self.code, "message": self.getMessage()})

    @staticmethod
    def from_json(input_json: str):
        return SerializableException()

    def getMessage(self) -> str:
        return self.message

    def __str__(self):
        return self.getMessage()


class InvalidAmountException(SerializableException):
    def __init__(self, *args):
        super().__init__(*args)
        self.code = 0
        self.message = "Invalid amount"

    @staticmethod
    def from_json(input_json: str):
        return InvalidAmountException()


class EmailAlreadyExistsException(SerializableException):
    def __init__(self, *args):
        super().__init__(*args)
        self.code = 1
        self.message = "Email already exists"

    @staticmethod
    def from_json(input_json: str):
        return EmailAlreadyExistsException()


class InvalidCredentialsException(SerializableException):
    def __init__(self, *args):
        super().__init__(*args)
        self.code = 2
        self.message = "Invalid credentials"

    @staticmethod
    def from_json(input_json: str):
        return InvalidCredentialsException()


class AccountNotFoundException(SerializableException):
    def __init__(self, *args):
        super().__init__(*args)
        self.code = 3
        self.message = "Account not found"

    @staticmethod
    def from_json(input_json: str):
        return AccountNotFoundException()


class InsufficientFundsException(SerializableException):
    def __init__(self, *args):
        super().__init__(*args)
        self.code = 4
        self.message = "Insufficient funds"

    @staticmethod
    def from_json(input_json: str):
        return InsufficientFundsException()


class SameAccountTransferException(SerializableException):
    def __init__(self, *args):
        super().__init__(*args)
        self.code = 5
        self.message = "Insufficient funds"

    @staticmethod
    def from_json(input_json: str):
        return SameAccountTransferException()


class InvalidAttributeValueException(SerializableException):
    def __init__(self, attribute_name, attribute_value, *args):
        super().__init__(*args)
        self.code = 6
        self.attribute_name = attribute_name
        self.attribute_value = attribute_value
        self.message = (
            f"Invalid attribute {self.attribute_name} = {self.attribute_value}"
        )

    def getMessage(self) -> str:
        self.message = (
            f"Invalid attribute value {self.attribute_name} = {self.attribute_value}"
        )
        return self.message

    @staticmethod
    def from_json(input_json: str):
        input_json = json.loads(input_json)
        return InvalidAttributeValueException(
            input_json["attribute_name"], input_json["attribute_value"]
        )

    def to_json(self) -> str:
        exp = json.loads(super().to_json())
        exp["attribute_name"] = self.attribute_name
        exp["attribute_value"] = self.attribute_value
        return json.dumps(exp)


# Mapping of exception code to exception class
exceptions_map: dict[int, SerializableException] = {
    0: InvalidAmountException,
    1: EmailAlreadyExistsException,
    2: InvalidCredentialsException,
    3: AccountNotFoundException,
    4: InsufficientFundsException,
    5: SameAccountTransferException,
    6: InvalidAttributeValueException,
}

"""
Converte a valid json string to SerializableException
"""


def ExceptionFromJSON(str_input_json) -> SerializableException:
    input_json = json.loads(str_input_json)

    # Check if code key is null
    if "code" not in input_json:
        raise Exception("Null exception code")

    # Check if code key is in exceptions map
    if input_json["code"] not in exceptions_map:
        raise Exception(f"Invalid exception code {input_json["code"]}")

    # User current SerializableException from_json method to convert
    # json string
    return exceptions_map[input_json["code"]].from_json(str_input_json)
