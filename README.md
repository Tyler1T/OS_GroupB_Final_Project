# OS_GroupB_Final_Project

to compile:
    gcc client.c -o client
    gcc server.c TrainSeatChecker.c -o server -pthread

to run:
    ./server 2
    NOTE: [1, 2, or 3 indicates server number]
in another terminal:
    ./client 2
    NOTE: [1, 2, or 3 indicates server number]
