#pragma once

extern volatile sig_atomic_t running;

void listen_for_shutdown(const int server_socket);
