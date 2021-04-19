# OS_GroupB_Final_Project

to compile:
    gcc client.c -o client
    gcc server.c TrainSeatChecker.c Summary.c -o server -pthread

to run:
    ./server 2
    NOTE: [1, 2, or 3 indicates server number]
in another terminal:
    ./client 2
    NOTE: [1, 2, or 3 indicates server number]

NOTE: when the client file is executed, it attempts to connect to the specified server. if successful, the server will respond with a menu once a thread becomes available.
currently, the only menu option that does anything is option 1 ("make a reservation"). the server asks the customer for information and then checks to see if there are enough seats available on the train. no reservation is made as of now.
