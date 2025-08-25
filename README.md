# C The Web

[![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)](<https://en.wikipedia.org/wiki/C_(programming_language)>)
[![Bash](https://img.shields.io/badge/Bash-4EAA25?logo=gnubash&logoColor=fff)](https://www.gnu.org/software/bash/)

This project serves as a learning experience for the fundamentals of C projects and bash scripting by developing a barebones web server.

Topics/features:

- Concurrency by thread pool
- Graceful shutdown by handling signals
- Makefile
- CI for C, specifically lints, memory checks, etc.
- C project structure
- Bash script to easily run server

## Local Reproduction

1. Load environment:
   ```bash
    set -a
    source .env
    set +a
   ```
2. Build project:
   ```bash
   make
   ```
3. Start server:
   ```bash
   chmod +x ./server.sh
   ./server.sh start
   ```
4. Go to http://127.0.0.1:8080/

5. Stop server and clean directory:
   ```bash
   ./server.sh stop
   make clean
   ```
