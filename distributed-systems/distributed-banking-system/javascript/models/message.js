export default class Message {
    constructor(type, id, obfReference, methodId, args, error = false) {
        this.type = type;
        this.id = id;
        this.obfReference = obfReference;
        this.methodId = methodId;
        this.arguments = args;
        this.error = error;
    }

    toJson() {
        return JSON.stringify({
            type: this.type,
            id: this.id,
            obfReference: this.obfReference,
            methodId: this.methodId,
            arguments: this.arguments,
            error: this.error
        });
    }

    static fromJson(jsonStr) {
        const data = JSON.parse(jsonStr);
        return new Message(
            data.type,
            data.id,
            data.obfReference,
            data.methodId,
            data.arguments,
            data.error
        );
    }

    toString() {
        return `----Message----\ntype=${this.type}\nid=${this.id}\nobfReference=${this.obfReference}\nmethodId=${this.methodId}\narguments=${this.arguments}\nerror=${this.error}\n---------------`;
    }
}