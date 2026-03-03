This project has been created as part of the 42 curriculum by *asinsard, thmaitre.*

## Description

**ft_irc** is a lightweight IRC (Internet Relay Chat) server implementation written in C++98. It adheres to the IRC protocol standards defined in RFC 2812 and provides essential server functionality for clients to communicate in real-time via channels and private messages.

### Key Features

- **Socket-based networking** using epoll for efficient multi-client handling
- **Channel management** with support for joining, leaving, and channel-specific operations
- **User authentication** through PASS command
- **Core IRC commands**:
  - `NICK`: Set or change user nickname
  - `USER`: Provide user information
  - `PASS`: Authenticate with server password
  - `JOIN`: Join one or more channels
  - `PART`: Leave channels
  - `PRIVMSG`: Send private messages or channel messages
  - `INVITE`: Invite users to channels
  - `KICK`: Remove users from channels
  - `TOPIC`: Set or view channel topics
  - `MODE`: Manage user and channel modes
  - `LIST`: List available channels
  - `QUIT`: Disconnect from server
- **Proper IRC protocol message formatting** with numeric replies
- **Signal handling** for graceful shutdown

## Instructions

### Compilation

Build the server using the provided Makefile:

```bash
make
```

To clean object files:
```bash
make clean
```

To remove all compiled files:
```bash
make fclean
```

To rebuild from scratch:
```bash
make re
```

### Execution

Run the server with the following syntax:

```bash
./ircserv <PORT> <PASSWORD>
```

**Parameters:**
- `<PORT>`: The port number the server will listen on (default IRC port is 6667)
- `<PASSWORD>`: Server password required for client authentication

**Examples:**

```bash
./ircserv 6667 mypassword
./ircserv 8080 secret123
```

**Help:**

```bash
./ircserv --help
./ircserv -h
```

### Connecting Clients

Once the server is running, connect using any IRC client (e.g., nc, telnet, or dedicated IRC clients):

```bash
nc localhost 6667
telnet localhost 6667
```

Then authenticate and use standard IRC commands.

## Resources

### RFC and Standards
- **[RFC 2812 - Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812)**: The official IRC protocol specification detailing message formats and command definitions
- **[RFC 2811 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)**: The official IRC protocol specification detailing channel management

### Socket Programming and Networking
- **Linux man pages**: `man socket`, `man bind`, `man listen`, `man epoll`, `man send`, `man recv`
- **The Linux Programming Interface**: pages **`1149`** to **`1285`**.

### C++ and System Programming
- **Cppreference.com**: C++ standard library reference

### Personal Notes
- [Sockets](./docs/Sockets.md): File detailing how sockets work.
- [RFC 2812 notes](./docs/RFC_2812_notes.md): File that deals with **`RFC 2812`** and compiles important information.
- [Function](./docs/funct.md): File detailing allowed function for the project.

### AI Assistance

AI was used in this project for the following purposes:
- **Documentation**: Helping for understanding RFC

## Project Structure

```
ft_irc/
├── sources/
│   ├── main.cpp              # Entry point
│   ├── server/               # Server core (socket, I/O, main loop)
│   ├── client/               # Client representation and state
│   ├── channel/              # Channel management
│   ├── command/              # Command implementations
│   ├── parse/                # Message parsing
│   ├── response/             # IRC protocol responses
│   ├── exception/            # Exception handling
│   └── signal/               # Signal handling
├── includes/                 # Header files (mirroring sources structure)
├── docs/
│   ├── funct.md             # Socket API documentation
│   └── RFC 2812 notes.md    # IRC protocol notes
├── Makefile                  # Build configuration
└── README.md                 # This file
```

## Technical Choices

- **epoll**: Used for efficient monitoring of multiple client connections
- **Factory Pattern**: Command factory for extensible command handling
- **Reply Handler**: Structure for handle replies and broadcast them
- **Exception Hierarchy**: Custom exceptions for different error types

## Testing

To test the server:

1. Start the server, with a chosen port and password
2. Connect multiple clients using the chosen interface.
3. Perform various IRC operations (JOIN, PRIVMSG, etc.)
4. Verify proper message routing and protocol compliance

Example testing session:
```bash
# Terminal 1: Start server
./ircserv 6667 testpass

# Terminal 2: Connect client 1
nc localhost 6667

# Terminal 3: Connect client 2
nc localhost 6667
```

Then type IRC commands in each client window to test functionality.

## Notes

- The server uses non-blocking sockets and epoll for efficient I/O
- All IRC messages are parsed and validated against the protocol
- The server gracefully handles client disconnections
- Signal handlers ensure clean shutdown and resource cleanup

