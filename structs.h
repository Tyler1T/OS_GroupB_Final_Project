

#ifndef structs
#define structs
struct clientInformation{
    char ClientName[50];
    char DateOfBirth[100];
    char Gender[10];
    int GovernmentID;
    char DateOfTravel[100];
    int NumberOfTravelers;
    char MenuOption[10];
}__attribute__((packed))clientInformation;
#endif
