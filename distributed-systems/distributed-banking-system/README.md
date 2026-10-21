# Distributed Monetary Transaction System

<div align="center">
  <a href="https://www.youtube.com/watch?v=ptZQre07_UQ" target="_blank" rel="noopener noreferrer">
    <img src="https://img.youtube.com/vi/ptZQre07_UQ/0.jpg" alt="GUI Showcase Video">
  </a>
</div>

A distributed banking system developed for the **Distributed Systems** course at the Federal University of Ceará (UFC), Quixadá Campus, in the 2024.2 semester.

The project explores remote service invocation over UDP, structured JSON messages, request/response correlation, and interoperability between clients implemented in different programming languages. The final version includes a Python server, Python and Node.js clients, and a graphical client built with Pygame.

## Features

- **Account creation** with email, name, password, and initial balance.
- **Account login** to retrieve account information and the current balance.
- **Deposits** into an authenticated account.
- **Transfers** between accounts.
- **Remote procedure calls (RPC-style)** through a client-side proxy and server-side dispatcher/skeleton.
- **Cross-language communication:** a Node.js client communicates with the Python server using the same JSON-over-UDP message protocol.
- **Graphical interface:** a Pygame-based frontend lets users log in, register, deposit funds, and transfer money.
- **Error handling:** application-level exceptions represent conditions such as invalid credentials, duplicate emails, invalid amounts, missing recipient accounts, insufficient funds, and transfers to the same account.
- **Incremental experiments:** separate Python variants explore packet-loss and delayed-response scenarios.

> **Note:** This is an academic project for studying distributed systems, not production banking software. It uses an in-memory account store and should not be used to handle real money or sensitive credentials.

## Architecture

The system follows a client-server architecture. Clients call methods on a local proxy; the proxy serializes a request and sends it to the server using UDP. The server decodes the message, dispatches the requested operation, invokes the banking service, and returns a JSON response.

```text
Python CLI / Pygame GUI / Node.js CLI
                 |
                 v
           Bank Proxy
                 |
                 v
        UDP + JSON messages
                 |
                 v
          Python UDP Server
                 |
                 v
             Dispatcher
                 |
                 v
           Bank Skeleton
                 |
                 v
          Banking Service
```

### Message protocol

Requests and responses are JSON objects with fields such as:

| Field | Purpose |
|---|---|
| `type` | Indicates whether the message is a request or a response. |
| `id` | Correlates a response with its original request and helps identify duplicate requests. |
| `obfReference` | Identifies the remote object/service; the current service is `Bank`. |
| `methodId` | Names the remote operation, such as `createAccount`, `loginAccount`, `deposit`, or `transfer`. |
| `arguments` | Contains the serialized operation arguments or result. |
| `error` | Indicates whether the response represents an application-level error. |

The shared JSON protocol allows the Node.js client to communicate with the Python server without requiring both sides to use the same programming language.

### Main components

- **`python/bank_server/udp_server.py`** — receives UDP datagrams and sends responses.
- **`python/bank_server/dispatcher.py`** — routes requests to the appropriate server-side skeleton method.
- **`python/bank_server/bank_skeleton.py`** — converts request arguments into model objects and calls the banking service.
- **`python/models/bank.py`** — implements account operations and business rules.
- **`python/bank_client/proxy_bank.py`** — exposes remote banking operations to Python clients.
- **`javascript/bank_client/proxy_bank.js`** — implements the corresponding proxy for Node.js.
- **`python_gui/main.py`** — provides the graphical interface using Pygame and Pygame GUI.

## Incremental Deliveries

The project was developed in four incremental deliveries, gradually building the distributed service and exploring communication behavior.

The included project variants show the following areas of the work:

- **Core implementation:** the Python server and client, remote method dispatch, JSON serialization, and banking operations.
- **Cross-language client:** a Node.js client implementing the same protocol to call the Python service.
- **Communication-failure experiments:** `python_exemplo_falhas_perda/` and `python_exemplo_falhas_demora/` contain variants configured to explore packet loss and delayed responses, including timeout and retry behavior.
- **Graphical client:** `python_gui/` adds a Pygame interface that uses the Python proxy to perform banking operations.

The folders in this archive are the available implementation variants; consult the course deliverables or commit history for the exact requirements and chronology of each submission.

## Technologies

- **Python** — server, banking logic, Python client, and graphical frontend.
- **Node.js (JavaScript ES modules)** — cross-language command-line client.
- **UDP sockets** — request/response transport.
- **JSON** — language-independent message serialization.
- **Pygame** — graphical application and window handling.
- **pygame_gui** — GUI widgets and interface layout.

## Project Structure

```text
.
├── python/
│   ├── bank_client/              # Python client proxy and UDP client
│   ├── bank_server/              # UDP server, dispatcher, and skeleton
│   ├── config/                   # Network and protocol settings
│   ├── models/                   # Bank, account, message, and exceptions
│   ├── utils/
│   ├── client.py                 # Example Python client
│   └── server.py                 # Python server entry point
├── javascript/
│   ├── bank_client/              # Node.js proxy, UDP client, and CLI
│   ├── models/                   # JavaScript protocol and account models
│   ├── configs.js                # Network and protocol settings
│   └── package.json
├── python_exemplo_falhas_perda/  # Packet-loss experiment variant
├── python_exemplo_falhas_demora/ # Delayed-response experiment variant
├── python_gui/                   # Pygame GUI and its Python proxy
└── RelatorioSistemaTransacaoMonetario.docx
```

## Requirements

Install the following before running the project:

- Python 3
- Node.js with npm
- Pygame and pygame_gui for the graphical client

Install the Python GUI dependencies:

```bash
python -m pip install pygame pygame_gui
```

The Python server and command-line client use the Python standard library. Run commands from the relevant project directory so the project's package imports resolve correctly.

## Running the System

The default server configuration uses UDP port `12000`. The server and clients must be able to reach the same server IP address and port.

### 1. Start the Python server

From the repository root:

```bash
cd python
python server.py
```

The server starts listening for UDP requests.

### 2. Run the Python client example

In another terminal:

```bash
cd python
python client.py
```

`client.py` is an example script, not an interactive command-line interface. Its operations and account values can be edited to test different scenarios.

### 3. Run the Node.js client

In another terminal:

```bash
cd javascript
npm install
npm run dev
```

The Node.js client provides an interactive CLI. Type `help` to see the available commands:

```text
createAccount <email> <name> <password>
login <email> <password>
deposit <email> <password> <amount>
transfer <email> <password> <recipient-email> <amount>
exit
```

Use accounts that exist on the currently running server. Since account data is stored in memory, restarting the server clears the accounts.

### 4. Run the Pygame GUI

Start the Python server first. Then, from the repository root, run:

```bash
cd python_gui
python main.py
```

The GUI includes registration and login screens, plus account actions for deposits and transfers. It communicates with the server through its bundled Python proxy.

## Configuration

Network settings are defined in each implementation's configuration files:

- Python server/client: `python/config/service_config.py`
- Node.js client: `javascript/configs.js`
- Pygame client proxy: `python_gui/bank_proxy/config/service_config.py`

The default port is `12000`, and the server address is derived from a local-host IP helper. For use across different machines, verify that the configured address resolves to the machine running the server and that UDP traffic on the chosen port is allowed by the firewall. Keep the server and client configurations consistent.

## Reliability Experiments

The `python_exemplo_falhas_perda/` and `python_exemplo_falhas_demora/` directories contain alternative implementations and timeout/retry settings for experiments involving packet loss and delayed responses.

UDP does not guarantee delivery, ordering, or duplicate protection by itself. The project therefore includes request identifiers, timeouts, and retry logic as part of its exploration of distributed communication. These mechanisms are educational examples and should not be interpreted as a complete reliability guarantee.

## Limitations

- Account data is kept in memory and is lost when the server stops.
- UDP delivery is not guaranteed.
- The system is intended for local/course demonstrations, not production use.
- Passwords and network messages do not implement production-grade security or encryption.
- The network configuration relies on a local-host IP helper and may need adjustment for multi-machine deployments.

## Academic Context

**Course:** Distributed Systems  
**Institution:** Federal University of Ceará (UFC), Quixadá Campus  
**Semester:** 2024.2

### Team

- Gustavo Gurgel Medeiros
- Jorge Eduardo Silva Sousa
- Mário Martins Aragão
- Matheus Conrado Pires

---

This repository documents an academic implementation of a distributed monetary transaction service, with a focus on remote invocation, UDP communication, protocol serialization, and interoperability between Python and JavaScript clients.
