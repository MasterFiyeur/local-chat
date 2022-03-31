# tcp-chat
Yet Another School Project

# Project architecture
### Board
This directory is reserved for functions and main.c that we need for displaying every message of the chat.
### Client
This directory is reserved for functions and main.c that we need for send a message to the server, display all connected users, etc. It's the client side program.
### Server
This directory is reserved for functions and main.c that we need manage request that come in the server. It's the server side program.
### Utils 
This directory is reserved for common functions that we will need in differents parts of the project.
### Samples
This directory contains example files gave by the teacher for understand UDP and TCP chat
### Output
This directory is reserved for executable files and for execute board, client or server. It may contains files ending by '.o', they can be cleaned using : 
```console
make clean
```

# Makefile using
## To compile and execute a part of project
### client, board or server
Go into the directory :
```console
cd <directory> 
```
Compile :
```console
make 
```
Execute :
```console
make execute
```

## To compile and execute the whole project
#### It will be changed to split in different bash
Compile :
```console
make 
```
Execute client, board or server:
```console
make client
make board
make server
```