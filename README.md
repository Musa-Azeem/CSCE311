# CSCE311 Project 2

## Directory Structure:
```
.
├── makefile
├── README.md
├── inc
│   ├── Unix-Domain-Socket.h
│   ├── text-server.h
│   ├── text-client.h
│   └── search.h
└── src
    ├── main-server.cc
    ├── main-client.cc
    ├── Unix-Domain-Socket.cc
    ├── text-server.cc
    ├── text-client.cc
    └── search.cc
```

## The following objects are defined in this directory:

    UnixDomainSocket
    TextServer
    TextClient
    Search


The ```inc``` folder contains all headers for the classes

The ```src``` folder contains all source code, as well as the main methods for server and client

## Objects

### UnixDomainSocket
- This class serves as a parent class for TextServer and TextClient, defining the attributes they share (the socket path)
- This class is included in ```text-server.h``` and ```text-client.h```

### TextServer
- This class defines a Unix Domain Socket Server.
- Clients connect to this server, providing a file path and search string to the server.
- The server then searches for the given string in the given file (using Search class), and sends any lines it finds back to the client.
- This class is included in ```main-server.cc```

### TextClient
- This class defines a Unix Domain Socket Client.
- An instance of this class is initialized with a file path and search string.
- The client sends the file path and search string to the server it connects to, and recieves the lines of the file containing that string from the server.
- This class is included in ```main-client.cc```

### Search
- This class is given a file path and search string and finds any instances of the given search string in the file.
- This class is included in ```text-server.cc```


