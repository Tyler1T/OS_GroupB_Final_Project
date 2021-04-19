#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int seatChecker();
int serve_customer(int socket, int id);
int get_client_info(int socket, struct clientInformation* c);
int thread_loop(void* args);
int main(int argc, char const *argv[]);

int connect_to_server(char* ip_addr, int port);
bool valid_ip(char *ip);
int main(int argc, char const *argv[]);
