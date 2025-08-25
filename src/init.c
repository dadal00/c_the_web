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
#include <sys/types.h>
// Internet related such as sockaddr_in and INADDR_ANY
#include <netinet/in.h>
/*
    Standard libary
    - exit
    - definition for EXIT_FAILURE
*/
#include <stdlib.h>
/*
    Standard Input/Output
    - printf
    - perror
*/
#include <stdio.h>

#include <init.h>

int init(const int port, const int max_connections) {
  /*
      Get a file descriptor for our server to listen as a connection
     Input/Output
      - AF_INET: address family, internet; IPv4 address
      - SOCK_STREAM: TCP Socket (Compared to a UDP socket)
      - IPPROTO_TCP: TCP Protocol (Compared to a UDP protocol)
  */
  int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  // File descriptor is always 0 or above, so if < 0, its an error
  if (server_socket == -1) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Defining the SERVER address + port
  struct sockaddr_in address;

  // IPv4 address
  address.sin_family = AF_INET;
  // Listen on all interfaces
  address.sin_addr.s_addr = INADDR_ANY;
  // Convert port from HOST to NETWORK byte order using htons
  address.sin_port = htons(port);

  // Tell the OS to send data from our SERVER address to our SOCKET file
  // descriptor If error, exit
  if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) == -1) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Transitions from normal CLIENT to SERVER socket by listening
  // - queues 3 connections so if 5, 2 will fail
  if (listen(server_socket, max_connections) == -1) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  return server_socket;
}
