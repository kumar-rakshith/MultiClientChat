# MultiChat - Multi-Client Chat Application

MultiChat is a simple and lightweight chat application designed to allow multiple clients to connect and interact with each other in real-time. It supports a server-client architecture, where the server can handle multiple clients concurrently using threads.

## Features
- **Multi-client support**: The server can handle multiple clients at the same time.
- **Real-time messaging**: Messages sent by any client are broadcasted to all other connected clients in real-time.
- **Threaded server**: Each client is handled in a separate thread, ensuring that communication remains responsive and efficient.

## Architecture
The system is based on a **server-client** model:
- The **Server** listens for incoming connections, accepts clients, and handles their messages.
- The **Client** sends messages to the server, and the server broadcasts these messages to all connected clients.

### **Key Components**
- **Server**: Handles client connections, message broadcasting, and client management.
- **Client**: Connects to the server, sends messages, and displays messages from other clients.
- **Common Utilities**: Shared utility functions for tasks like trimming newline characters from user input.

## Installation

## 1. Clone the Repository
To get started, clone the repository to your local machine:

```bash
git clone https://github.com/kumar-rakshith/MultiChat.git
```

## 2. Compile the Server and Client

Navigate to the `server` directory and compile the server:

```bash
cd server
make
```

Next, navigate to the `client` directory and compile the client:

```bash
cd client
make
```

## 3. Running the Server
To start the server, run the following command in the `server` directory:

```bash
./server
```

## 4. Running the Client
To connect to the server, run the client from the `client` directory. You will need to provide the IP address of the machine running the server:

```bash
./client
```

Multiple clients can be started either on the same machine or across different machines by modifying the server IP in the client code.

## Usage
- When you start the client, it will ask you for a name. Once entered, you can begin chatting.
- All clients connected to the server will receive the messages in real-time.
- Messages from a client are broadcast to all other connected clients.

## Example Workflow
1. Start the server on one machine or terminal.
2. Start multiple clients on the same or different machines.
3. Once clients are connected, they can send messages to each other.
4. All clients will receive the messages in real-time.

## Contributing
Feel free to fork the repository, submit issues, or send pull requests to improve the application. Contributions are welcome!

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.
```

This version is properly formatted in **Markdown** and includes all the necessary instructions for setting up, compiling, and running your multi-client chat application!
