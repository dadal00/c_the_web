/*
    Standard Input/Output
    - printf
    - perror
*/
#include <stdio.h>
/*
    Standard libary
    - exit
    - definition for EXIT_FAILURE
*/
#include <stdlib.h>
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
#include <pthread.h>
#include <unistd.h>

#include <listeners.h>
#include <signals.h>

static const char response[] = "HTTP/1.1 200 OK\n"
                               "Content-Type: text/plain\n"
                               "Content-Length: 13\n\n"
                               "Hello, world!";

static void *start_listener(void *arg) {
  int server_socket = *(int *)arg;

  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);

  while (running) {
    int client_socket;

    // Blocks until new connection, creates a new client socket (file
    // descriptor) fit for the server information
    // - 1 connection at a time from the queue
    if ((client_socket = accept(server_socket, (struct sockaddr *)&address,
                                &addrlen)) == -1) {
      if (!running) {
        fprintf(stdout, "Exiting thread\n");
        break;
      }

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

  return NULL;
}

void start_listeners(const int server_socket, const int thread_count) {
  pthread_t threads[thread_count];

  for (int i = 0; i < thread_count; i++) {
    if ((pthread_create(&threads[i], NULL, start_listener,
                        (void *)&server_socket)) != 0) {
      fprintf(stderr, "Failed to create thread\n");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < thread_count; i++)
    pthread_join(threads[i], NULL);
}
