#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#ifndef header
#define header

#define NUM_THREADS 2

struct clientInformation{
    char ClientName[50];
    char DateOfBirth[50];
    char Gender[10];
    int GovernmentID;
    char DateOfTravel[50];
    int NumberOfTravelers;
    int MenuOption;
    char seats[100];
    char modified[100];
    int server;
}__attribute__((packed))clientInformation;

struct customer_queue {
    pthread_t threads[NUM_THREADS];
    int sockets[100];
    int waiting;
    int first;
};

int seatChecker();

int create_socket(int port, struct sockaddr_in* address);
int initialize_semaphores_threads(struct customer_queue* q);
int serve_customer(int socket, int id);
int get_client_info(int socket, struct clientInformation* c);
int verify_enough_seats(int socket, struct clientInformation* c);
int thread_loop(void* args);
int main(int argc, char const *argv[]);

int connect_to_server(char* ip_addr, int port);
bool valid_ip(char *ip);
int main(int argc, char const *argv[]);

void modifySummary(struct clientInformation *customer);
void addNewCustomer(struct clientInformation *customer);
void changeOldCustomer(struct clientInformation *customer, int line);
int findCustomer(int ID);
#endif
