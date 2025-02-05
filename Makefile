
CC = gcc
CFLAGS = -pthread
SERVER_SRC = server/server.c
CLIENT_SRC = client/client.c
SERVER_OUT = server
CLIENT_OUT = client

all: $(SERVER_OUT) $(CLIENT_OUT)

$(SERVER_OUT): $(SERVER_SRC)
	$(CC) $(CFLAGS) $(SERVER_SRC) -o $(SERVER_OUT)

$(CLIENT_OUT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $(CLIENT_SRC) -o $(CLIENT_OUT)

clean:
	rm -f $(SERVER_OUT) $(CLIENT_OUT)
