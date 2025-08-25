#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for close()
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
// for sockaddr_in
#include <netinet/in.h>
// handle termination signal
#include <signal.h>

int server_socket;

static void handle_shutdown(int sig) {
  // Marks as intentionally unused
  (void)sig;

  printf("\nShutting down server...\n");

  if (server_socket >= 0)
    close(server_socket);

  exit(0);
}

int main() {
  // Shutdown signals for graceful shutdown
  // Signal for terminal by interrupt like CtrlC
  signal(SIGINT, handle_shutdown);
  // Signal for termination by command like kill
  signal(SIGTERM, handle_shutdown);

  /*
      Get a file descriptor for our server to listen as a connection
     Input/Output
      - AF_INET: address family, internet; IPv4 address
      - SOCK_STREAM: TCP Socket (Compared to a UDP socket)
      - IPPROTO_TCP: TCP Protocol (Compared to a UDP protocol)
  */
  server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  // File descriptor is always 0 or above, so if < 0, its an error
  if (server_socket < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Defining the SERVER address + port
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // IPv4 address
  address.sin_family = AF_INET;
  // Listen on all interfaces
  address.sin_addr.s_addr = INADDR_ANY;
  // Convert port from HOST to NETWORK byte order using htons
  address.sin_port = htons(8080);

  // Tell the OS to send data from our SERVER address to our SOCKET file
  // descriptor If error, exit
  if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Transitions from normal CLIENT to SERVER socket by listening
  // - queues 3 connections so if 5, 2 will fail
  if (listen(server_socket, 3) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }
  printf("Server listening on http://127.0.0.1:8080/ ...\n");
  fflush(stdout);

  char *response = "HTTP/1.1 200 OK\n"
                   "Content-Type: text/plain\n"
                   "Content-Length: 13\n\n"
                   "Hello, world!";

  while (1) {
    // Blocks until new connection, creates a new client socket (file
    // descriptor) fit for the server information
    // - 1 connection at a time from the queue
    int client_socket = accept(server_socket, (struct sockaddr *)&address,
                               (socklen_t *)&addrlen);
    if (client_socket < 0) {
      perror("accept failed");
      continue;
    }

    // Send data over client socket
    // - last input is special flags, this case is no special flags
    send(client_socket, response, strlen(response), 0);
    close(client_socket);

    printf("Processed request...\n");
    fflush(stdout);
  }

  return 0;
}
