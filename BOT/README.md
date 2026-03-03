*This project has been created as part of the 42 curriculum by thmaitre.*

## Description

FeurBot is an IRC (Internet Relay Chat) bot written in C++98 that connects to an IRC server and participates in channels by responding to messages. 

### Key Features

- Connects to an IRC server on localhost:6667
- Automatically discovers and joins all available channels
- Responds with "feur!" when triggered

### Technical Stack

- **Language**: C++98
- **Protocol**: IRC (RFC 2812)
- **Socket API**: POSIX sockets (socket.h, netinet/in.h, arpa/inet.h)
- **Build System**: Makefile

## Instructions

### Compilation

To compile the project, run:

```bash
make
```

### Clean Build

To remove object files and start fresh:

```bash
make re          # Clean and rebuild
```

### Execution

To run the bot:

```bash
./feurbot
```

**Prerequisites:**
- An IRC server running on `127.0.0.1:6667`
- C++ compiler supporting C++98 standard
- POSIX-compliant system (Linux, macOS, etc.)

**Configuration:**
Currently, the bot connects to `127.0.0.1:6667`. To change the server, modify the constants in `includes/FeurBot.hpp`:

```cpp
namespace server {
    const int PORT = 6667;
    const std::string HOST = "127.0.0.1";
}
```

### Signal Handling

The bot gracefully handles termination signals (SIGINT, SIGTERM) through a custom signal handler. Send `CTRL+C` or kill the process to cleanly disconnect from the IRC server.

## Resources

### IRC Documentation
- [RFC 1459 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)
- [IRC Commands Reference](https://www.irchelp.org/protocol/rfc.html)

### C++ and Socket Programming
- [POSIX Socket Programming](https://pubs.openacm.org/socket-programming/)
- [Linux man pages: socket(2), connect(2), recv(2), send(2)](https://man7.org/linux/man-pages/)

### French Internet Culture
- [Quoi? Feur! - Know Your Meme](https://knowyourmeme.com/) (search for "quoifeur")

### How AI Was Used

AI assistance was utilized for:
- **Testing and debugging**: Diagnostic advice for connection and message parsing issues

The core logic, IRC message parsing, channel joining, and the "quoifeur" response mechanism were implemented through manual development and testing.
