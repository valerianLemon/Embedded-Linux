CCC=gcc
Dependencies=Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o

# PHONY on 'clean' and 'all', since these are not explicit objects

.PHONY: clean all

# Make all programs at once

all: TCPChatServer TCPChatClient	


# TCPChatServer program compilation

TCPChatServer: TCPChatServer.o $(Dependencies)
	$(CCC) TCPChatServer.o $(Dependencies) -o TCPChatserver

TCPChatServer.o: TCPChatServer.c Auxiliary.h CreateTCPServerSocket.h AcceptTCPConnection.h HandleTCPClient.h
	$(CCC) -c TCPChatServer.c

# TCPChatClient program compilation

TCPChatClient: TCPChatClient.o Auxiliary.o CreateTCPClientSocket.o
	$(CCC) TCPChatClient.o Auxiliary.o CreateTCPClientSocket.o -o TCPChatClient

TCPChatClient.o: TCPChatClient.c Auxiliary.h CreateTCPClientSocket.h
	$(CCC) -c TCPChatClient.c

# Independant functions without 'main'

Auxiliary.o: Auxiliary.c Auxiliary.h
	$(CCC) -c Auxiliary.c

CreateTCPServerSocket.o: CreateTCPServerSocket.c CreateTCPServerSocket.h
	$(CCC) -c CreateTCPServerSocket.c

CreateTCPClientSocket.o: CreateTCPClientSocket.c Auxiliary.h
	$(CCC) -c CreateTCPClientSocket.c

AcceptTCPConnection.o: AcceptTCPConnection.c Auxiliary.h AcceptTCPConnection.h
	$(CCC) -c AcceptTCPConnection.c

HandleTCPClient.o: Auxiliary.h HandleTCPClient.h
	$(CCC) -c HandleTCPClient.c

# Clean the directory by removing all files ending on '.o' or named by a program with a 'main' function.

clean:
	rm *.o TCPChatServer TCPChatClient
