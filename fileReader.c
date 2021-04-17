#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void fileWriter(struct clientInformation *customer);

int main(int argc, char const *argv[]) {
    struct clientInformation c;
    struct clientInformation *info = &c;

    strcpy(c.ClientName, "Tyler");
    strcpy(c.DateOfBirth, "6/23/1999");
    strcpy(c.Gender, "Male");
    strcpy(c.DateOfTravel, "1/1/2021");
    c.GovernmentID = 15;
    c.NumberOfTravelers = 3;

    fileWriter(info);

    return 0;
}

void fileWriter(struct clientInformation *customer){
    FILE* summary = fopen("Summary.txt", "w");
    fprintf(summary, "%s, ", &customer->ClientName);
    fprintf(summary, "%s, ", customer->DateOfBirth);
    fprintf(summary, "%s, ", customer->Gender);
    fprintf(summary, "%d, ", customer->GovernmentID);
    fprintf(summary, "%s, ", customer->DateOfTravel);
    fprintf(summary, "%d, ", customer->NumberOfTravelers);
    fprintf(summary, "%d\n", customer->MenuOption);





}
