# OS_GroupB_Final_Project

to compile:
    gcc client.c -o client
    gcc server.c AdditionalFunction.c Summary.c -o server -pthread

to run:
    ./server 2
    NOTE: [1, 2, or 3 indicates server number]
in another terminal:
    ./client 2
    NOTE: [1, 2, or 3 indicates server number]

NOTES:
when the client file is executed, it attempts to connect to the specified server. if successful, the server will respond with a menu once a thread becomes available.

we have 3 servers, each with 3 threads.
we have 2 trains, train_1 = today's date, train_2 = tomorrow's date.
each train has 20 seats.

when modifying, we only allow customers to change which seats are reserved, or reduce the number of seats. additional seats requires a new reservation.

only one thread is allowed to access the train1.txt and train2.txt files at a time,
but multiple threads can read summary.txt at one time as long as no other thread is  writing to it.
