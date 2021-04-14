/*  Group B
 *  Client Driver File
 *  Authors: nathan_baker
 *  Email: nathan.t.baker@okstate.edu
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
 #include <unistd.h>
 #include <string.h>
 #include <stdbool.h>
 #include <fcntl.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <sys/wait.h>

 bool valid_ip(char *ip) { // return whether a string is a valid ip address
     struct sockaddr_in sa;
     int result = inet_pton(AF_INET, ip, &(sa.sin_addr));
     return result != 0;
 }

int ask_server(char* ip_addr, int port) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nsocket creation error.\n");
        return -1;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0) {
        printf("\ninvalid address.\n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nconnection failed.\n");
        return -1;
    }
    return sock;
}

int main(int argc, char const *argv[]) {
    int port = 0;
    if (argc > 1) port = atoi(argv[1]);
    if (port > 4 || port < 1) {
        printf("no valid server index provided.\n");
        exit(1);
    }
    char ip_addr[15];
    strcpy(ip_addr,"127.0.0.1"); // LOCALHOST

    fork();
    fork();
    fork();
    int sock = ask_server(ip_addr,8000+port);
    if (sock == -1) exit(1);
    char m[100];
    if (read(sock, &m, sizeof(m)) < 0) {
        printf("\nread error.\n");
        return -1;
    }
    printf("%s\n",m);
    int a;
    if (read(sock, &a, sizeof(int)) < 0) {
        printf("\nread error.\n");
        return -1;
    }
    if (a == -1) exit(0);
    if (read(sock, &m, sizeof(m)) < 0) {
        printf("\nread error.\n");
        return -1;
    }
    printf("%s\n",m);
    return 0;
}
