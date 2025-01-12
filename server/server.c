#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 5000
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

// Define the client structure
typedef struct {
    int socket;
    struct sockaddr_in address;
    char name[50]; // Store the client's name
} client_t;

client_t *clients[MAX_CLIENTS]; // Array to store all clients
int client_count = 0; // Active client count
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function to broadcast message to all clients
void broadcast_message(char *message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i]->socket != sender_socket) {
            if (send(clients[i]->socket, message, strlen(message), 0) == -1) {
                perror("Error sending message to client");
            }
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

// Function to handle each client
void *handle_client(void *arg) {
    client_t *client = (client_t *)arg;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        // Receive message from the client
        int bytes_received = recv(client->socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            printf("Client %s disconnected.\n", client->name);
            break;
        }

        // Format the message with the sender's name
        snprintf(message, sizeof(message), "%s: %s", client->name, buffer);
        printf("%s", message);

        // Broadcast the message to all other clients
        broadcast_message(message, client->socket);
    }

    // Remove the client from the list when they disconnect
    pthread_mutex_lock(&clients_mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i]->socket == client->socket) {
            for (int j = i; j < client_count - 1; j++) {
                clients[j] = clients[j + 1];
            }
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&clients_mutex);

    // Clean up
    close(client->socket);
    free(client);
    return NULL;
}

int main() {
    int server_socket;
    struct sockaddr_in server_addr;

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming client connections
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    while (1) {
        // Accept a new client connection
        int client_socket;
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        // Get the client's name
        char client_name[50];
        recv(client_socket, client_name, sizeof(client_name), 0);

        // Allocate memory for the new client and add them to the list
        client_t *new_client = (client_t *)malloc(sizeof(client_t));
        new_client->socket = client_socket;
        new_client->address = client_addr;
        strncpy(new_client->name, client_name, sizeof(new_client->name) - 1);

        pthread_mutex_lock(&clients_mutex);
        clients[client_count++] = new_client;
        pthread_mutex_unlock(&clients_mutex);

        // Create a new thread to handle the client
        pthread_t tid;
        if (pthread_create(&tid, NULL, handle_client, (void *)new_client) != 0) {
            perror("Thread creation failed");
            close(client_socket);
            free(new_client);
        }
    }

    close(server_socket);
    return 0;
}
