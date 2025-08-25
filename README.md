# C The Web

FIRST

set -a
source .env
set +a

THEN

make format
make

THEN

chmod +x ./server.sh
./server.sh start

FINALLY

./server.sh stop
make clean
