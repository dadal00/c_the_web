/*
    Standard Input/Output
    - printf
    - perror
*/
#include <stdio.h>
/*
    Socket related
    - socket
    - bind
    - listen
    - accept
    - send
    - definitions for Constants such as SOCK_STREAM
*/
#include <sys/socket.h>
// Internet related such as sockaddr_in and INADDR_ANY
#include <netinet/in.h>
// Strings for strlen
#include <string.h>
// POSIX libary for close
#include <unistd.h>

#include <listen.h>

static const char response[] = "HTTP/1.1 200 OK\n"
                               "Content-Type: text/plain\n"
                               "Content-Length: 13\n\n"
                               "Hello, world!";

void start_listener(const int server_socket) {
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);
  while (1) {
    int client_socket;

    // Blocks until new connection, creates a new client socket (file
    // descriptor) fit for the server information
    // - 1 connection at a time from the queue
    if ((client_socket = accept(server_socket, (struct sockaddr *)&address,
                                &addrlen)) == -1) {
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
}
