#pragma once

typedef struct {
  int port;
  int max_connections;
} ServerConfig;

ServerConfig load_env(void);
