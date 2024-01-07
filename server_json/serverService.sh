#!/bin/bash

export LD_LIBRARY_PATH=~/Qt/Tools/QtCreator/lib/Qt/lib:$LD_LIBRARY_PATH
SERVER_DIR="/home/mohanad/build-server_test-Desktop_Qt_6_6_1_GCC_64bit-Release"
LOG_FILE="$SERVER_DIR/server_message.log"
EXECUTABLE="$SERVER_DIR/server_test"
RESTART_DELAY=5

while true; do

    cd "$SERVER_DIR"

    echo "Start the server in the background using systemd............."

    nohup "$EXECUTABLE" &>> "$LOG_FILE"  

    echo "The process id of the server is $!.........."
    echo "The error code of the service is $?........"

    # Add a delay before attempting to restart
    sleep $RESTART_DELAY
done
