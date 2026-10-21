import json


class Message:
    # Construtor da mensagem
    def __init__(self, type, id, obfReference, methodId, arguments, error=False):
        self.type = type
        self.id = id
        self.obfReference = obfReference
        self.methodId = methodId
        self.arguments = arguments
        self.error = error

    # Retorna a representação JSON da mensagem
    def to_json(self):
        return json.dumps(
            {
                "type": self.type,
                "id": self.id,
                "obfReference": self.obfReference,
                "methodId": self.methodId,
                "arguments": self.arguments,
                "error": self.error,
            }
        )

    # Função stática que retornar lé uma mensagem de um JSON
    @staticmethod
    def from_json(json_str):
        data = json.loads(json_str)
        return Message(
            data["type"],
            data["id"],
            data["obfReference"],
            data["methodId"],
            data["arguments"],
            data["error"],
        )

    def __str__(self):
        return f"""----Message----
type={self.type}
id={self.id}
obfReference={self.obfReference}
methodId={self.methodId}
arguments={self.arguments}
error={self.error}
---------------"""
