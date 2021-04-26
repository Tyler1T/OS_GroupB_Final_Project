// GROUP B
// Nathan Baker
// nathan.t.baker@okstate.edu

#include "header.h"

pthread_mutex_t lock;

int get_client_info(int socket, struct clientInformation* c) {
    char m[1000];
    strcpy(m,"0Please enter your full name: ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    sscanf(m,"%50[^\n]",c->ClientName);
    printf("%s\n",c->ClientName);
    strcpy(m,"0Please enter your date of birth [MM/DD/YYYY]: ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    sscanf(m,"%50[^\n]",c->DateOfBirth);
    printf("%s\n",c->DateOfBirth);
    strcpy(m,"0Please enter your gender [M, F, Other]: ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    sscanf(m,"%10[^\n]",c->Gender);
    printf("%s\n",c->Gender);
    strcpy(m,"0Please enter your date of GovernmentID number: ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    sscanf(m,"%d",&c->GovernmentID);
    printf("%d\n",c->GovernmentID);
    strcpy(m,"0Please enter your desired date of travel [MM/DD/YYYY]: ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    sscanf(m,"%50[^\n]",c->DateOfTravel);
    printf("%s\n",c->DateOfTravel);
    strcpy(m,"0Please enter the number of travelers: ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    sscanf(m,"%d",&c->NumberOfTravelers);
    printf("%d\n",c->NumberOfTravelers);
    return 0;
}

int change_read_count(int train, int offset) {
    FILE *fp;
    if (train == 1) {
        fp = fopen ("train1_read_count.txt", "r");
    } else if (train == 2) {
        fp = fopen ("train2_read_count.txt", "r");
    }
    int num;
    if (fp == NULL) num = 0;
    else {
        fscanf(fp,"%d", &num);
        fclose(fp);
    }
    if (offset == 0) return num;
    if (train == 1) {
        fp = fopen ("train1_read_count.txt", "w");
    } else if (train == 2) {
        fp = fopen ("train2_read_count.txt", "w");
    }
    fprintf(fp,"%d",num+offset);
    fclose(fp);
    return num+offset;
}

int verify_enough_seats(int socket, int train, struct clientInformation* c) {
    char m[1000];
    if (train == -1) {
        strcpy(m,"1Sorry, there is no train available for the selected date.\nReservation cancelled.\n");
        send(socket, &m, sizeof(m), MSG_NOSIGNAL);
        return -1;
    }
    char r_train_sem_name[13];
    char w_train_sem_name[14];
    snprintf(r_train_sem_name,13,"/train%d_read",train);
    snprintf(w_train_sem_name,14,"/train%d_write",train);
    sem_t* sem_train_r;
    sem_t* sem_train_w;
    if ((sem_train_r = sem_open(r_train_sem_name, O_RDWR)) == SEM_FAILED) {
        printf("failed to open read semaphore for train%d.\nerror number:%d",train,errno);
        exit(1);
    }
    if ((sem_train_w = sem_open(w_train_sem_name, O_RDWR)) == SEM_FAILED) {
        printf("failed to open write semaphore for train%d.\nerror number:%d",train,errno);
        exit(1);
    }
    sem_wait(sem_train_r);
    change_read_count(train,1);
    if (change_read_count(train,0) == 1) sem_wait(sem_train_w);
    sem_post(sem_train_r);
    int available = seatChecker(train);
    sem_wait(sem_train_r);
    change_read_count(train,-1);
    if (change_read_count(train,0) == 0) sem_post(sem_train_w);
    sem_post(sem_train_r);
    if ((c->NumberOfTravelers) > available) {
        snprintf(m,1000,"1Sorry, there are only %d seats availble for the selected date.\nReservation cancelled.\n",available);
        send(socket, &m, sizeof(m), MSG_NOSIGNAL);
        return -1;
    }
    return 0;
}

int confirm_purchase(int socket, int train, struct clientInformation* c) {
    char m[1000];
    snprintf(m,1000,"0\nDo you want to make reservation (yes/no): ");
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
    read(socket, &m, sizeof(m));
    if (strcmp(m,"yes") == 0) {
        char w_train_sem_name[14];
        snprintf(w_train_sem_name,14,"/train%d_write",train);
        sem_t* sem_train_w;
        if ((sem_train_w = sem_open(w_train_sem_name, O_RDWR)) == SEM_FAILED) {
            printf("failed to open write semaphore for train%d.\nerror number:%d",train,errno);
            exit(1);
        }
        sem_wait(sem_train_w);
        return 0;
    } else {
        snprintf(m,1000,"1Reservation cancelled.\n");
        send(socket, &m, sizeof(m), MSG_NOSIGNAL);
        return -1;
    }
}

void send_available_seats(int socket, int train, struct clientInformation* c) {
    // char r_train_sem_name[13];
    // char w_train_sem_name[14];
    // snprintf(r_train_sem_name,13,"/train%d_read",train);
    // snprintf(w_train_sem_name,14,"/train%d_write",train);
    // sem_t* sem_train_r;
    // sem_t* sem_train_w;
    // if ((sem_train_r = sem_open(r_train_sem_name, O_RDWR)) == SEM_FAILED) {
    //     printf("failed to open read semaphore for train%d.\nerror number:%d",train,errno);
    //     exit(1);
    // }
    // if ((sem_train_w = sem_open(w_train_sem_name, O_RDWR)) == SEM_FAILED) {
    //     printf("failed to open write semaphore for train%d.\nerror number:%d",train,errno);
    //     exit(1);
    // }
    // sem_wait(sem_train_r);
    // change_read_count(train,1);
    // if (change_read_count(train,0) == 1) sem_wait(sem_train_w);
    // sem_post(sem_train_r);
    char output[100];
    showAvailable(train, output);
    // sem_wait(sem_train_r);
    // change_read_count(train,-1);
    // if (change_read_count(train,0) == 0) sem_post(sem_train_w);
    // sem_post(sem_train_r);
    char m[1000];
    snprintf(m,1000,"0\nPlease choose %d of the following available seats [single space between each seat]:\n%s\n",c->NumberOfTravelers,output);
    send(socket, &m, sizeof(m), MSG_NOSIGNAL);
}

void showAvailable(int trainNum, char* output) {
    FILE *fp ;
    char c;

    printf("Opening the file train in read mode \n");
    if (trainNum == 1) {
        fp = fopen ("train1.txt","r"); // opening an existing file
    }
    else if (trainNum == 2) {
        fp = fopen ("train2.txt", "r"); // opening an existing file
    }
    if ( fp == NULL ) {
      printf ("Could not open file train \n");
      return;
    }
    printf("Reading the file train \n");
    int count = 0;
    int char_index = 0;
    while (1) {
        c = fgetc (fp); // reading the file
        if (c == '0') {
            output[char_index++] = 'A'+(count / 5);
            output[char_index++] = '0'+(count % 5 + 1);
        } else if (c == '1') {
            output[char_index++] = '-';
            output[char_index++] = '-';
        } else {
            output[char_index++] = '\0';
            break;
        }
        output[char_index++] = ' ';
        count++;
        if ((count % 5) == 0) output[char_index++] = '\n';
    }
    printf("Closing the file train \n") ;
    fclose (fp) ; // Closing the file
    return;

}

int check_seat(int train, int row, int column) {
    if (!(row < 5 && row >= 0 && column < 5 && column >= 0)) return -1;
    FILE *fp;
    if (train == 1) {
        fp = fopen ("train1.txt", "r");
    } else if (train == 2) {
        fp = fopen ("train2.txt", "r");
    }
    int index = row*5 + column;
    printf("%d, %d, %d\n",row, column, index);
    char c;
    for (int i=0; i<index; i++) {
        c = fgetc(fp);
    }
    c = fgetc(fp);
    fclose(fp);
    if (c == '0') return 0;
    else return -1;
}

int write_seat(int train, int row, int column) {
    FILE *fp;
    if (train == 1) {
        fp = fopen ("train1.txt", "r+");
    } else if (train == 2) {
        fp = fopen ("train2.txt", "r+");
    }
    int index = row*5 + column;
    fseek(fp, index, SEEK_SET);
    fputc('1',fp);
    fclose(fp);
    return 0;
}

int verify_selection(int socket, int train, struct clientInformation* c, char* m) {
    char n[1000];
    strcpy(n,m);
    printf("%s\n",n);
    for (int i=0; i<c->NumberOfTravelers; i++) {
        if (i>0) memmove(n, n+3, 1000);
        char seat[3];
        sscanf(n,"%2c",seat);
        int row = seat[0] - 65;
        int column = seat[1] - 49;
        if (check_seat(train,row,column) == -1) {
            printf("seat verification failed.\n");
            char w_train_sem_name[14];
            snprintf(w_train_sem_name,14,"/train%d_write",train);
            sem_t* sem_train_w;
            if ((sem_train_w = sem_open(w_train_sem_name, O_RDWR)) == SEM_FAILED) {
                printf("failed to open write semaphore for train%d.\nerror number:%d",train,errno);
                exit(1);
            }
            sem_post(sem_train_w);
            return -1;
        }
    }
    return 0;
}

int update_train(int train, struct clientInformation* c, char* m) {
    char output[100];
    showAvailable(train, output);
    printf("%s\n",output);
    char n[1000];
    strcpy(n,m);
    for (int i=0; i<c->NumberOfTravelers; i++) {
        if (i>0) memmove(n, n+3, 1000);
        char seat[3];
        sscanf(n,"%2c",seat);
        int row = seat[0] - 65;
        int column = seat[1] - 49;
        write_seat(train,row,column);
    }
    addNewCustomer(c);
    char w_train_sem_name[14];
    snprintf(w_train_sem_name,14,"/train%d_write",train);
    sem_t* sem_train_w;
    if ((sem_train_w = sem_open(w_train_sem_name, O_RDWR)) == SEM_FAILED) {
        printf("failed to open write semaphore for train%d.\nerror number:%d",train,errno);
        exit(1);
    }
    sem_post(sem_train_w);
    showAvailable(train, output);
    printf("%s\n",output);
    return 0;
}

int serve_customer(int socket, int id) {
    struct clientInformation c;
    char m[1000];
    int first = 1;
    while (1) {
        if (first) {
            snprintf(m,1000,"0Hello! My name is THREAD-%d, How may I assist you today?\n\t1. Make a reservation.\n\t2. Inquiry about a ticket.\n\t3. Modify the reservation.\n\t4. Cancel the reservation.\n\t5. Exit the program.\n",id);
            first = 0;
        } else {
            strcpy(m,"0\nIs there anything else I can help you with today?\n\t1. Make a reservation.\n\t2. Inquiry about a ticket.\n\t3. Modify the reservation.\n\t4. Cancel the reservation.\n\t5. Exit the program.\n");
        }
        send(socket, &m, sizeof(m), MSG_NOSIGNAL);
        read(socket, &m, sizeof(m));
        sscanf(m,"%d",&c.MenuOption);
        printf("%d\n",c.MenuOption);
        if (c.MenuOption == 5) { // make reservation
            strcpy(m,"2Exiting...Thank you and have a good day!\n");
            send(socket, &m, sizeof(m), MSG_NOSIGNAL);
            return 0;
        }
        if (c.MenuOption == 1) { // make reservation
            if (get_client_info(socket,&c) == -1) continue;
            char date[50];
            int train;
            GetTodayDate(date);
            printf("%s\n",date);
            if (strcmp(c.DateOfTravel,date) == 0) train = 1;
            else {
                GetTomorrowDate(date);
                if (strcmp(c.DateOfTravel,date) == 0) train = 2;
                else train = -1;
            }
            if (verify_enough_seats(socket, train, &c) == -1) continue;
            if (confirm_purchase(socket, train, &c) == -1) continue;
            send_available_seats(socket, train, &c);
            read(socket, &m, sizeof(m));
            if (verify_selection(socket, train, &c, m) == -1) continue;
            update_train(train, &c, m);
            snprintf(m,1000,"1Reservation confirmed! Your ticket number is %d.\n",c.ticket);
            send(socket, &m, sizeof(m), MSG_NOSIGNAL);
            continue;
        }
        break;
    }
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

int create_socket(int port, struct sockaddr_in* address) {
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(1);
    } else {
        printf("Server socket created\n");
    }
    address->sin_family = AF_INET;
    address->sin_addr.s_addr = INADDR_ANY;
    address->sin_port = htons(8000+port);
    if (bind(server_fd, (struct sockaddr*) address, sizeof(*address)) < 0) {
        perror("bind failed");
        exit(1);
    } else {
        printf("Server socket bound\n");
    }
    if (listen(server_fd, 2) < 0) {
        perror("listen");
        exit(1);
    } else {
        printf("Server socket is listening\n");
    }
    return server_fd;
}

int initialize_semaphores_threads(struct customer_queue* q, int reset_semaphores) {
    q->first = q->waiting = 0;
    pthread_mutex_init(&lock, NULL);
    for (int i=0; i<NUM_THREADS; i++) {
        if (pthread_create(&(q->threads[i]), NULL, (void *)&thread_loop, (void *)q) != 0) {
            perror("Failed to create thread");
        }
    }
    if (reset_semaphores == 1) {
        sem_unlink("/train1_read");
        sem_unlink("/train2_read");
        sem_unlink("/train1_write");
        sem_unlink("/train2_write");
    }
    if ((sem_open("/train1_read", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        printf("failed to open semaphore for train0.\nerror number:%d",errno);
        exit(1);
    }
    if ((sem_open("/train2_read", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        printf("failed to open semaphore for train1.\nerror number:%d",errno);
        exit(1);
    }
    if ((sem_open("/train1_write", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        printf("failed to open semaphore for train0.\nerror number:%d",errno);
        exit(1);
    }
    if ((sem_open("/train2_write", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR, 1)) == SEM_FAILED) {
        printf("failed to open semaphore for train1.\nerror number:%d",errno);
        exit(1);
    }
}

int server_loop(int server_fd, int port, struct sockaddr_in* address, struct customer_queue* q) {
    while(1) {
        int addrlen = sizeof(*address);
        int new_socket;
        if ((new_socket = accept(server_fd, (struct sockaddr*) address,(socklen_t*) &addrlen)) < 0) {
            perror("Could not accept connection.");
            exit(1);
        }
        printf("new socket accepted.\n");
        char m[1000];
        pthread_mutex_lock(&lock);
        if (q->waiting < 100) {
            q->sockets[q->first+q->waiting] = new_socket;
            q->waiting = q->waiting + 1;
            snprintf(m,1000,"0Thank you for choosing Server %d. One of our threads will be with you shortly...\n",port);
            send(new_socket, &m, sizeof(m), 0);
        } else {
            snprintf(m,1000,"2Sorry, There are already %d customers waiting to be served. Please try again later.\n",100);
            send(new_socket, &m, sizeof(m), 0);
        }
        pthread_mutex_unlock(&lock);
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    int port = 0;
    if (argc > 1) port = atoi(argv[1]);
    if (port > 4 || port < 1) {
        printf("no valid server index provided.\n");
        exit(1);
    }
    int reset = 0;
    if (argc > 2 && strcmp(argv[2],"-r") == 0) reset = 1;
    struct sockaddr_in address;
    int server_fd = create_socket(port, &address);
    struct customer_queue q;
    initialize_semaphores_threads(&q, reset);
    server_loop(server_fd,port,&address,&q);
    return 0;
}
