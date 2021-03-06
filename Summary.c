#include "header.h"

/**
 * Author: Tyler Tucker
 * Email: <tyler.m.tucker@okstate.edu>
 * Date: April 19th, 2020
 * Program Description: This file takes input from the server and then
    determines if a customer is in the summary file or not. The functions can
    also change information in the summary file and delete customers completely
 */


/*
    The addNewCustomer function takes a new customers information and apends
    it to the end of the summary.txt, it also sets the customer ticket number
*/
void addCustomer(struct clientInformation *customer, int new) {
    FILE* summary = fopen("Summary.txt", "a");

    if (new == 1) {
        customer->ticket = -1;
        customer->ticket = findCustomer(customer);
    }

    fprintf(summary, "%d, ", customer->ticket);
    fprintf(summary, "%s, ", customer->ClientName);
    fprintf(summary, "%s, ", customer->DateOfBirth);
    fprintf(summary, "%s, ", customer->Gender);
    fprintf(summary, "%d, ", customer->GovernmentID);
    fprintf(summary, "%s, ", customer->DateOfTravel);
    fprintf(summary, "%d, ", customer->NumberOfTravelers);
    fprintf(summary, "%s, ", customer->seats);

    if(new == 0){
        fprintf(summary, "%d, ", customer->server);
        fprintf(summary, "%s\n", customer->modified);
    }else{
        fprintf(summary, "%d\n", customer->server);
    }


    fclose(summary);
}


/*
    The changeOldCustomer function will take a returning customers information
    and changed what they have in the summary file to reflect the newer
    information
*/
void changeOldCustomer(struct clientInformation *customer){
    deleteCustomer(customer,1);
    addCustomer(customer,0);
}

/*
    The printCustomerInfo function will take a customer, find them in the
    summary file, and print their info to a buffer array
*/
void printCustomerInfo(struct clientInformation *customer, char *output){
    FILE* summary = fopen("Summary.txt", "r");
    char buffer[1024];
    int line = findCustomer(customer);
    int counter = 0;

    while((fgets(buffer, 1024, summary)) != NULL){
        if(counter == line){
            strcpy(output, "Inquiry results: ");
            strcat(output, buffer);
            fclose(summary);
            return;
        }

        counter++;
    }
    strcpy(output, "No results found");
    fclose(summary);
}

/*
    The deleteCustomer function will take a customer and look for it in the
    summary file, it then deletes that person by writing everyone else to a temp
    file and then deleting the summary file and renaming the temp file
*/
void deleteCustomer(struct clientInformation *customer, int modifying){
    FILE* summary = fopen("Summary.txt", "r");
    FILE* temp = fopen("temp.txt", "a");
    char buffer[1024];
    int counter = 0;
    int line = findCustomer(customer);
    printf("line: %d",line);
    while((fgets(buffer, 1024, summary)) != NULL){
        if(counter != line){
            fprintf(temp, "%s", buffer);
        } else {
            if (modifying == 0) {
                fprintf(temp, "%d, Reservation was cancelled.\n",customer->ticket);
            }
        }
        counter++;
    }

    fclose(summary);
    fclose(temp);
    remove("summary.txt");
    rename("temp.txt", "summary.txt");
}


/*
    findCustomer looks at the summary file and tries to find a given ID
    If that ID is found then it will return the line where the ID is
    Otherwise the function returns -1
*/
int findCustomer(struct clientInformation *customer){
    FILE* summary = fopen("Summary.txt", "r");
    char buffer[1024];
    int temp = 0;
    int line = 0;
    int ticket = 0;
    ticket = customer->ticket;
    while(fgets(buffer, 1024, summary)){
        sscanf(buffer, "%d",  &temp);
        if(temp == ticket){
            fclose(summary);
            return line;
        }
        line++;
    }
    fclose(summary);
    return line;
}

/*
    findCustomerTicket uses a ticket number to find the customer in the summary
    file then returns what line to customer is on if they exist and -1 if they don't
*/
int findCustomerTicket(int ticket){
    FILE* summary = fopen("Summary.txt", "r");
    char buffer[1024];
    int temp = 0;
    int line = 0;
    while(fgets(buffer, 1024, summary)){
        sscanf(buffer, "%d",  &temp);
        if(temp == ticket){
            fclose(summary);
            return line;
        }
        line++;
    }
    fclose(summary);
    return line;
}

/*
    createCustomer function take a customer's struct and puts their information
    into the summary text file
*/
void createCustomer(struct clientInformation *customer){
    FILE* summary = fopen("Summary.txt", "r");
    char buffer[1024];
    int temp = 0;
    int line = 0;
    int ticket = customer->ticket;
    while(fgets(buffer, 1024, summary)){
        printf("%s\n", buffer);
        sscanf(buffer, "%d",  &temp);
        if(temp == ticket){
            sscanf(buffer, "%*[^,], %[^,]",  customer->ClientName);
            sscanf(buffer, "%*[^,], %*[^,], %[^,]",  customer->DateOfBirth);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %[^,]",  customer->Gender);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %*[^,], %d",  &customer->GovernmentID);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %[^,]",  customer->DateOfTravel);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %d",  &customer->NumberOfTravelers);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %[^,]",  customer->seats);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %d",  &customer->server);
            sscanf(buffer, "%*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %*[^,], %[^\n]",  customer->modified);

            line++;
            break;
        }
    }

    fclose(summary);

    if(line == 0) printf("Customer was not found\n");
}
