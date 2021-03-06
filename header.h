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
#include <time.h>

#ifndef header
#define header

#define NUM_THREADS 3

struct clientInformation{
    char ClientName[50];
    char DateOfBirth[50];
    char Gender[10];
    int GovernmentID;
    char DateOfTravel[50];
    int NumberOfTravelers;
    int MenuOption;
    char seats[100];
    int ticket;
    char modified[200];
    int server;
}__attribute__((packed))clientInformation;

struct customer_queue {
    pthread_t threads[NUM_THREADS];
    int seats_for_thread[2*NUM_THREADS];
    int sockets[100];
    int waiting;
    int first;
    int port;
};

// AdditionalFunction.c
int seatChecker(int trainNum);
int GetTomorrowDate(char *tomorrowsDate);
int GetTodayDate(char *todaysDate);

// server.c
int create_socket(int port, struct sockaddr_in* address);
int initialize_semaphores_threads(struct customer_queue* q, int reset);
int thread_loop(void* args);
int serve_customer(int socket, int t_id, int s_id, int* seats_for_thread);
int get_customer_info(int socket, struct clientInformation* c);
int get_customer_ticket(int socket, struct clientInformation* c);
int get_train(struct clientInformation* c);
int change_read_count(int offset);
int signal_write(int train);
int wait_write(int train);
int signal_read(int train);
int wait_read(int train);
int check_thread_permission(int id, int train, int seats, int* seats_for_thread);
int verify_enough_seats(int socket, int train, struct clientInformation* c);
int confirm_purchase(int socket, int train, struct clientInformation* c);
int confirm_cancel(int socket, struct clientInformation* c);
int confirm_modify(int socket, struct clientInformation* c);
void show_available(int trainNum, char* output);
void send_available_seats(int socket, int train, struct clientInformation* c);
int check_seat(int train, int row, int column);
int verify_selection(int socket, int train, struct clientInformation* c, char* m);
int write_seat(int train, int row, int column, int update);
int add_to_train(int train, struct clientInformation* c, char* m);
int remove_from_train(struct clientInformation* c, int train);
int server_loop(int server_fd, int port, struct sockaddr_in* address, struct customer_queue* q);
int main(int argc, char const *argv[]);

// client.c
int connect_to_server(char* ip_addr, int port);
int main(int argc, char const *argv[]);

// Summary.c
void addCustomer(struct clientInformation *customer, int new);
void changeOldCustomer(struct clientInformation *customer);
void deleteCustomer(struct clientInformation *customer, int modifying);
void printCustomerInfo(struct clientInformation *customer, char *output);
int findCustomer(struct clientInformation *customer);
void createCustomer(struct clientInformation *customer);
int findCustomerTicket(int ticket);

#endif
