CCC=gcc
Dependencies=Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o CreateTCPClientSocket.o

# PHONY on 'clean' and 'all', since these are not explicit objects

.PHONY: clean all

# Make all programs at once

all: TCPEchoServer-Thread TCPChatClient

# TCPChatServer program compilation

TCPEchoServer-Thread: TCPEchoServer-Thread.o
	$(CCC) TCPEchoServer-Thread.o $(Dependencies) -o TCPEchoServer-Thread -lpthread

TCPEchoServer-Thread.o: TCPEchoServer-Thread.c $(Dependencies)
	$(CCC) -c TCPEchoServer-Thread.c -lpthread

# TCPChatClient program compilation

TCPChatClient: TCPChatClient.o
	$(CCC) TCPChatClient.o Auxiliary.o CreateTCPClientSocket.o -o TCPChatClient -lpthread

TCPChatClient.o: TCPChatClient.c $(Dependencies) 
	$(CCC) -c TCPChatClient.c

# Independant functions without 'main'

Auxiliary.o: Auxiliary.c Auxiliary.h
	$(CCC) -c Auxiliary.c

CreateTCPServerSocket.o: CreateTCPServerSocket.c CreateTCPServerSocket.h Auxiliary.c Auxiliary.h
	$(CCC) -c CreateTCPServerSocket.c

AcceptTCPConnection.o: AcceptTCPConnection.c Auxiliary.h AcceptTCPConnection.h
	$(CCC) -c AcceptTCPConnection.c

HandleTCPClient.o: Auxiliary.h HandleTCPClient.h HandleTCPClient.c Auxiliary.c
	$(CCC) -c HandleTCPClient.c

CreateTCPClientSocket.o: CreateTCPClientSocket.c CreateTCPClientSocket.h Auxiliary.h Auxiliary.c
	$(CCC) -c CreateTCPClientSocket.c


# Clean the directory by removing all files ending on '.o' or named by a program with a 'main' function.

clean:
	rm *.o TCPEchoServer-Thread TCPChatClient
