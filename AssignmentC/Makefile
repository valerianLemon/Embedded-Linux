CCC=gcc
Dependencies=Auxiliary.o AcceptTCPConnection.o CreateTCPServerSocket.o HandleTCPClient.o

# PHONY on 'clean' and 'all', since these are not explicit objects

.PHONY: clean all

# Make all programs at once

all: TCPEchoServer TCPEchoClient	


# TCPEchoServer program compilation

TCPEchoServer: TCPEchoServer.o $(Dependencies)
	$(CCC) TCPEchoServer.o $(Dependencies) -o TCPEchoserver

TCPEchoServer.o: TCPEchoServer.c Auxiliary.h CreateTCPServerSocket.h AcceptTCPConnection.h HandleTCPClient.h
	$(CCC) -c TCPEchoServer.c

# TCPEchoClient program compilation

TCPEchoClient: TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o
	$(CCC) TCPEchoClient.o Auxiliary.o CreateTCPClientSocket.o -o TCPEchoClient

TCPEchoClient.o: TCPEchoClient.c Auxiliary.h CreateTCPClientSocket.h
	$(CCC) -c TCPEchoClient.c

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
	rm *.o TCPEchoServer TCPEchoClient
