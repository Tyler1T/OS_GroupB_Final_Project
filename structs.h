

#ifndef structs
#define structs
struct clientInformation{
    char ClientName[50];
    char DateOfBirth[100];
    char Gender[10];
    int GovernmentID;
    char DateOfTravel[100];
    int NumberOfTravelers;
    int MenuOption;
    char seats[100];
    char modified[100];
    int server;
}__attribute__((packed))clientInformation;
#endif
