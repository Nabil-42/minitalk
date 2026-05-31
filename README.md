# minitalk

[![Language](https://img.shields.io/badge/Language-C-A8B9CC?style=flat&logo=c)](https://github.com/Nabil-42/minitalk)
[![School](https://img.shields.io/badge/%C3%89cole_42-Paris-00babc?style=flat)](https://42.fr)
[![Norminette](https://img.shields.io/badge/Norminette-compliant-brightgreen?style=flat)](https://github.com/42School/norminette)

Inter-process communication (IPC) program using UNIX signals to transmit strings between a client and a server.

## Description

`minitalk` implements a simple communication protocol between two processes using only `SIGUSR1` and `SIGUSR2` signals. Each character is encoded bit by bit: `SIGUSR1` represents `0`, `SIGUSR2` represents `1`. The server decodes the signal stream and reconstructs the original message.

## How It Works

```
Client                          Server
  │                               │
  │  send PID of server           │
  │  encode char → 8 bits         │
  │  SIGUSR1 (bit=0) ──────────▶  │  receive signal
  │  SIGUSR2 (bit=1) ──────────▶  │  decode bit → accumulate → print char
  │  (repeat for each char)       │
  │  send null byte to signal EOT │
```

## Usage

```bash
# Terminal 1 — start server (prints its PID)
./server

# Terminal 2 — send a message
./client <server_PID> "Hello, World!"
```

## Stack

- **Language**: C
- **Key concepts**: UNIX signals (`sigaction`, `SIGUSR1`, `SIGUSR2`), bitwise operations, inter-process communication

## 42 Project Info

| Field | Value |
|-------|-------|
| **Project** | minitalk |
| **Circle** | 3 |
| **Norminette** | Compliant |

## What I Learned

- How UNIX signals work (`kill`, `sigaction`, `sigemptyset`)
- Encoding data as a bit stream using signal sequences
- Handling asynchronous events and signal-safe code constraints