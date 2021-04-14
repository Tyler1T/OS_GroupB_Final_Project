/*  Group B
 *  Server Driver File
 *  Authors: nathan_baker
 *  Email: nathan.t.baker@okstate.edu
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <pthread.h>

#define NUM_THREADS 6
pthread_mutex_t lock;

struct customer_queue {
    pthread_t threads[NUM_THREADS];
    int sockets[100];
    int waiting;
    int first;
};

int serve_customer(int socket, int id) {
    sleep(2);
    char m[100];
    snprintf(m,100,"Hello! My name is THREAD-%d, How may I assist you today?",id);
    send(socket, &m, sizeof(m), 0);
    printf("sent.\n");
    return 0;
}

int thread_loop(void* args) {
    struct customer_queue* q = (struct customer_queue*) args;
    int id;
    for (int i=0; i<NUM_THREADS; i++) {
        if (q->threads[i] == pthread_self()) {
            id = i;
            break;
        }
    }
    while(1) {
        int my_customer = -1;
        pthread_mutex_lock(&lock);
        if (q->waiting > 0) {
            my_customer = q->sockets[q->first];
            q->sockets[q->first] = 0;
            q->first = q->first + 1;
            q->waiting = q->waiting -1;
        }
        pthread_mutex_unlock(&lock);
        if (my_customer >= 0) serve_customer(my_customer,id);
    }
}

int main(int argc, char const *argv[]) {
    int port = 0;
    if (argc > 1) port = atoi(argv[1]);
    if (port > 4 || port < 1) {
        printf("no valid server index provided.\n");
        exit(1);
    }
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(1);
    } else {
        printf("Server socket created\n");
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8000+port);
    if (bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(1);
    } else {
        printf("Server socket bound\n");
    }
    if (listen(server_fd, 4) < 0) {
        perror("listen");
        exit(1);
    } else {
        printf("Server socket is listening\n");
    }
    struct customer_queue q;
    q.first = q.waiting = 0;
    pthread_mutex_init(&lock, NULL);
    for (int i=0; i<NUM_THREADS; i++) {
        if (pthread_create(&(q.threads[i]), NULL, (void *)&thread_loop, (void *)&q) != 0) {
            perror("Failed to create thread");
        }
    }
    while(1){
        if ((new_socket = accept(server_fd, (struct sockaddr*) &address,
                (socklen_t*) &addrlen)) < 0) {
            perror("Could not accept connection.");
            exit(1);
        } else {
            printf("New socket accepted\n");
        }
        char m[100];
        pthread_mutex_lock(&lock);
        if (q.waiting < 100) {
            q.sockets[q.first+q.waiting] = new_socket;
            q.waiting = q.waiting + 1;
            snprintf(m,100,"Thank you for choosing Server %d. One of our threads will be with you shortly...",port);
            send(new_socket, &m, sizeof(m), 0);
            int success = 0;
            send(new_socket, &success, sizeof(int), 0);
        } else {
            snprintf(m,100,"Sorry, There are already %d customers waiting to be served. Please try again later.",100);
            send(new_socket, &m, sizeof(m), 0);
            int error = -1;
            send(new_socket, &error, sizeof(int), 0);
        }
        pthread_mutex_unlock(&lock);
    }
    return 0;
}
