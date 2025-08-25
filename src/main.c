/*
    Standard Input/Output
    - printf
    - perror
*/
#include <stdio.h>
// Standard library for EXIT_SUCESS
#include <stdlib.h>
// POSIX libary for close
#include <unistd.h>

// Custom
#include <config.h>
#include <init.h>
#include <listeners.h>
#include <signals.h>

int main() {
  // Load env
  ServerConfig config = load_env();

  // Start server
  int server_socket = init(config.port, config.max_connections);

  // Start handlers for graceful shutdown
  listen_for_shutdown(server_socket);

  printf("Server listening on http://127.0.0.1:%d/ ...\n", config.port);
  fflush(stdout);

  start_listeners(server_socket, config.num_threads);

  return EXIT_SUCCESS;
}
