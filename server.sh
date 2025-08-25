#!/bin/bash

PID_FILE="./server.pid"
EXEC=${FINAL_BINARY}

case "$1" in
start)
    if [ -f $PID_FILE ]; then
        echo "Server already running."

        exit 1
    fi

    # Run in background
    nohup ./"$EXEC" > server.log 2>&1 &

    # Save the PID
    echo $! > "$PID_FILE"

    echo "Server started. Output is being logged to server.log."
    ;;
stop)
    if [ ! -f $PID_FILE ]; then
        echo "Server not running."

        exit 1
    fi

    # Kill process
    kill $(cat $PID_FILE)

    # Clean up process saving
    rm $PID_FILE

    echo "Server stopped"
    ;;
restart)
    $0 stop

    $0 start
    ;;
*)
    echo "Usage: $0 start|stop|restart"
esac
