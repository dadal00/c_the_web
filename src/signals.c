#include <signal.h>
/*
    Standard libary
    - exit
    - definition for EXIT_FAILURE
*/
#include <stdlib.h>
// POSIX libary for close
#include <unistd.h>
/*
    Standard Input/Output
    - printf
    - perror
*/
#include <stdio.h>

#include <signals.h>

static int internal_server_socket = -1;

static void handle_shutdown(const int sig) {
  // Marks as intentionally unused
  (void)sig;

  printf("\nShutting down server...\n");

  if (internal_server_socket >= 0)
    close(internal_server_socket);

  exit(EXIT_SUCCESS);
}

void listen_for_shutdown(const int server_socket) {
  // Passing in server socket to close later
  internal_server_socket = server_socket;

  // Shutdown signals for graceful shutdown
  // Signal for terminal by interrupt like CtrlC
  signal(SIGINT, handle_shutdown);
  // Signal for termination by command like kill
  signal(SIGTERM, handle_shutdown);
}
