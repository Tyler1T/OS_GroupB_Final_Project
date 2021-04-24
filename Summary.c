#include "header.h"



/**
 * Author: Tyler Tucker
 * Email: <tyler.m.tucker@okstate.edu>
 * Date: April 19th, 2020
 * Program Description: This file takes input from the server and then
    determines if a customer is in the summary file or not
 */

int main(int argc, char const *argv[]) {
    struct clientInformation c;
    struct clientInformation *info = &c;

    strcpy(c.ClientName, "Tyler");
    strcpy(c.DateOfBirth, "6/23/1999");
    strcpy(c.Gender, "Male");
    strcpy(c.DateOfTravel, "1/1/2021");
    c.GovernmentID = 15;
    c.NumberOfTravelers = 3;
    c.MenuOption = 2;

    struct clientInformation b;
    struct clientInformation *infoB = &b;

    strcpy(b.ClientName, "Tom");
    strcpy(b.DateOfBirth, "6/23/1999");
    strcpy(b.Gender, "Male");
    strcpy(b.DateOfTravel, "1/1/2021");
    b.GovernmentID = 2;
    b.NumberOfTravelers = 3;
    b.MenuOption = 2;

    modifySummary(infoB);
    modifySummary(info);

    b.NumberOfTravelers = 10;
    modifySummary(infoB);

    return 0;
}


/*
    The addNewCustomer function takes a new customers information and apends
    it to the end of the summary.txt
*/
void addNewCustomer(struct clientInformation *customer){
    FILE* summary = fopen("Summary.txt", "a");

    fprintf(summary, "%s, ", customer->ClientName);
    fprintf(summary, "%s, ", customer->DateOfBirth);
    fprintf(summary, "%s, ", customer->Gender);
    fprintf(summary, "%d, ", customer->GovernmentID);
    fprintf(summary, "%s, ", customer->DateOfTravel);
    fprintf(summary, "%d, ", customer->NumberOfTravelers);
    fprintf(summary, "%d\n", customer->MenuOption);

    fclose(summary);
}


/*
    The changeOldCustomer function will take a returning customers information
    and changed what they have in the summary file to reflect the newer
    information
*/
void changeOldCustomer(struct clientInformation *customer){
    FILE* summary = fopen("Summary.txt", "w");
    char buffer[1024];
    int line = findCustomer(customer->GovernmentID);
    int counter;
	while((fgets(buffer, 1024, summary)) != NULL){
		if(counter == line){
		    fprintf(summary, "%s, ", customer->ClientName);
            fprintf(summary, "%s, ", customer->DateOfBirth);
            fprintf(summary, "%s, ", customer->Gender);
            fprintf(summary, "%d, ", customer->GovernmentID);
            fprintf(summary, "%s, ", customer->DateOfTravel);
            fprintf(summary, "%d, ", customer->NumberOfTravelers);
            fprintf(summary, "%d\n", customer->MenuOption);
		}else{
			fprintf(summary, "%s", buffer);
		}

        counter++;
	}

    fclose(summary);
}

void printCustomerInfo(char *output, int ticket){
    FILE* summary = fopen("Summary.txt", "r");
    char buffer[1024];
    int line = findCustomer(ticket);
    int counter;

	while((fgets(buffer, 1024, summary)) != NULL){
		if(counter == line){
			sscanf(output, "%s", buffer);
            fclose(summary);
            return;
		}
        counter++;
	}
}

/*
    The deleteCustomer function will take a customer and look for it in the
    summary file, it then deletes that person by writing everyone else to a temp
    file and then deleting the summary file and renaming the temp file
*/
void deleteCustomer(struct clientInformation *customer){
    FILE* summary = fopen("Summary.txt", "w+");
    FILE* temp = fopen("temp.txt", "a");
    char buffer[1024];
    int counter;
    int line = findCustomer(customer->GovernmentID);
	while((fgets(buffer, 1024, summary)) != NULL){
		if(counter != line){
			fprintf(temp, "%s", buffer);
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
int findCustomer(int ID){
    FILE* summary = fopen("Summary.txt", "r");
    char buffer[1024];
    int temp, line;
    while(fgets(buffer, 1024, summary)){
        sscanf(buffer, "%*[^,], %*[^,], %*[^,], %d",  &temp);
        if(temp == ID){
            fclose(summary);
            return line;
        }
        line++;
    }

    fclose(summary);
    return -1;
}


/*
    modifySummary function is used to determine whether or not there is a new customer
    being served, they could not be found in the summary file, or if this is a
    returning customer that is changing their information
*/
void modifySummary(struct clientInformation *customer){
    int option = customer->MenuOption;
    if(option == 1) addNewCustomer(customer);
    else if(option == 3) changeOldCustomer(customer);
    else if(option == 4) deleteCustomer(customer);
    else printf("Not an option\n");
}
