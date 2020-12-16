CC=gcc
Dependencies=Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o
LPFLAGS=-lpthread

# PHONY on 'clean' and 'all', since these are not explicit objects

.PHONY: clean all

# Make all programs at once

all: TCPEchoServer-Thread TCPEchoClient	


# TCPChatServer program compilation

TCPEchoServer-Thread: TCPEchoServer-Thread.o $(Dependencies)
	$(CC) TCPEchoServer-Thread.o $(Dependencies) -o TCPEchoServer-Thread $(LPFLAGS)

TCPEchoServer-Thread.o: Auxiliary.h CreateTCPServerSocket.h AcceptTCPConnection.h HandleTCPClient.h
	$(CC) -c TCPEchoServer-Thread.c -lpthread

# TCPEchoClient program compilation

TCPEchoClient: TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o
	$(CC) TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o -o TCPEchoClient

TCPEchoClient.o: TCPEchoClient.c Auxiliary.h CreateTCPClientSocket.h
	$(CC) -c TCPEchoClient.c

# Independant functions without 'main'

Auxiliary.o: Auxiliary.c Auxiliary.h
	$(CC) -c Auxiliary.c

CreateTCPServerSocket.o: CreateTCPServerSocket.c CreateTCPServerSocket.h
	$(CC) -c CreateTCPServerSocket.c

AcceptTCPConnection.o: AcceptTCPConnection.c Auxiliary.h AcceptTCPConnection.h
	$(CC) -c AcceptTCPConnection.c

HandleTCPClient.o: Auxiliary.h HandleTCPClient.h
	$(CC) -c HandleTCPClient.c

CreateTCPClientSocket.o: CreateTCPClientSocket.c Auxiliary.h
	$(CC) -c CreateTCPClientSocket.c


# Clean the directory by removing all files ending on '.o' or named by a program with a 'main' function.

clean:
	rm *.o TCPEchoServer-Thread TCPChatClient