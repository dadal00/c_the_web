#pragma once

typedef struct {
  int port;
  int max_connections;
  int num_threads;
} ServerConfig;

ServerConfig load_env(void);
