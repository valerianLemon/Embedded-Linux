CC = gcc
LIBS = -lncurses -lmenu
CFLAGS = -O2 -Wall -Werror
SERVER_DEPENDENCIES = Auxiliary.o ../server/AcceptTCPConnection.o ../server/CreateTCPServerSocket.o ../server/HandleTCPClient.o CommunicationProtocol.o ../server/SharedMemory.o ../server/ServerSemaphores.o
CLIENT_DEPENDENCIES = Auxiliary.o ../client/CreateTCPClientSocket.o ../client/MainMenu.o CommunicationProtocol.c

# PHONY on 'clean' and 'all', since these are not explicit objects

.PHONY: clean all

# Make all programs at once
all: Server Client

# TCPChatServer program compilation

Server: ../server/Server.o $(SERVER_DEPENDENCIES)
	$(CC) ../server/Server.o $(SERVER_DEPENDENCIES) -o ../server/Server -lrt -lpthread

Server.o: ../server/Server.c Auxiliary.h ../server/CreateTCPServerSocket.h ../server/AcceptTCPConnection.h ../server/HandleTCPClient.h ../server/ServerSemaphores.h
	$(CC) -c ../server/Server.c

# Client program compilation

Client: ../client/Client.o $(CLIENT_DEPENDENCIES)
	$(CC) ../client/Client.o $(CLIENT_DEPENDENCIES) -o ../client/Client $(LIBS)

Client.o: ../client/Client.c Auxiliary.h ../client/CreateTCPClientSocket.h
	$(CC) -c ../client/Client.c

# Independant functions without 'main'
SharedMemory.o: Auxiliary.h ../server/SharedMemory.c 
	$(CC) -c ../server/SharedMemory.c 

CommunicationProtocol.o: CommunicationProtocol.h
	$(CC) -c CommunicationProtocol.c

Auxiliary.o: Auxiliary.c Auxiliary.h
	$(CC) -c Auxiliary.c
	
ServerSemaphores.o: ../server/ServerSemaphores.c ../server/ServerSemaphores.h
	$(CC) -c ../server/ServerSemaphores.c


CreateTCPServerSocket.o: ../server/CreateTCPServerSocket.c ../server/CreateTCPServerSocket.h
	$(CC) -c ../server/CreateTCPServerSocket.c

CreateTCPClientSocket.o: ../cleent/CreateTCPClientSocket.c Auxiliary.h
	$(CC) -c ../cleent/CreateTCPClientSocket.c

AcceptTCPConnection.o: AcceptTCPConnection.c Auxiliary.h AcceptTCPConnection.h
	$(CC) -c ../server/AcceptTCPConnection.c

HandleTCPClient.o: Auxiliary.h ../server/HandleTCPClient.h CommunicationProtocol.h
	$(CC) -c ../server/HandleTCPClient.c 

# Clean the directory by removing all files ending on '.o' or named by a program with a 'main' function.


clean:
	rm *.o ../server/*.o ../client/*.o ../server/Server ../client/Client

