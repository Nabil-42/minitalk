# Usage — minitalk

## Start the server

```bash
./server
```

The server prints its PID and waits for incoming signals.

## Send a message

```bash
./client <server_PID> "Your message here"
```

Example:

```bash
# Terminal 1
$ ./server
Server PID: 12345

# Terminal 2
$ ./client 12345 "Hello from minitalk!"
# Server output: Hello from minitalk!
```

## Notes

- Messages are transmitted bit by bit via SIGUSR1 (bit 0) and SIGUSR2 (bit 1)
- The server handles one client at a time
- Supported characters: ASCII printable + Unicode (bonus version)