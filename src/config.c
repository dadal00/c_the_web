typedef enum { DONT_CHECK_PORT = 0, CHECK_PORT = 1 } PortCheckFlag;

/*
    Standard Input/Output
    - printf
    - perror
*/
#include <stdio.h>
#include <stdlib.h>

#include <config.h>

static const char *getenv_or_default(const char *name,
                                     const char *default_value) {
  const char *val = getenv(name);

  if (!val) {
    fprintf(stdout, "No env variable for %s. Using default of %s.\n", name,
            default_value);
  }

  return val ? val : default_value;
}

static int verify_positive_int(const char *value, const int check_port) {
  int value_int = atoi(value);
  if (value_int <= 0) {
    fprintf(stderr, "Invalid positive integer: %s\n", value);
    exit(EXIT_FAILURE);
  }

  if (check_port && value_int > 65535) {
    fprintf(stderr, "Invalid port: %s\n", value);
    exit(EXIT_FAILURE);
  }

  return value_int;
}

ServerConfig load_env(void) {
  int max_connections = verify_positive_int(
      getenv_or_default("MAX_CONNECTIONS", "3"), DONT_CHECK_PORT);

  int port = verify_positive_int(getenv_or_default("PORT", "8080"), CHECK_PORT);

  return (ServerConfig){port, max_connections};
}
