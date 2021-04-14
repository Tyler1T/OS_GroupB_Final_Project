#include "functions.h"
#include "structs.h"

void Manager()
{
	struct clientInformation c;
	struct clientInformation *client = &c;

	int i = 0;


	while(1)
	{
		system("clear");
		printf("Please enter the corresponding number for the option \nyou'd like from the following: \n\n1. Make a reservation.\n2. Inquiry about a ticket.\n3. Modify the reservation.\n4. Cancel the reservation.\n5. Exit the program.\n");
		printf("\nEnter here: ");
		fgets(client->MenuOption, sizeof(client->MenuOption), stdin);

		while(client->MenuOption[i] != '\n')
		{
			i++;
		}

		client->MenuOption[i] = client->MenuOption[i + 1];
		i = 0;

		if(strcmp(client->MenuOption, "1") == 0)
		{
			system("clear");
			printf("Please enter your full name: \n");
			fgets(client->ClientName, sizeof(client->ClientName), stdin);

			while(client->ClientName[i] != '\n')
			{
				i++;
			}

			client->ClientName[i] = client->ClientName[i + 1];
			i = 0;

			// printf("Please enter your Date of Birth (MM/DD/YYYY): \n");
			// fgets(client->DateOfBirth, sizeof(client->DateOfBirth), stdin);

			// while(client->DateOfBirth[i] != '\n')
			// {
			// 	i++;
			// }

			// client->DateOfBirth[i] = client->DateOfBirth[i + 1];
			// i = 0;

			// printf("Please enter your Gender (M/F/OTHER): \n");
			// fgets(client->Gender, sizeof(client->Gender), stdin);

			// while(client->Gender[i] != '\n')
			// {
			// 	i++;
			// }

			// client->Gender[i] = client->Gender[i + 1];
			// i = 0;

			// printf("Please enter your Government ID Number: \n");
			// fgets(client->GovernmentID, sizeof(client->GovernmentID), stdin);

			// while(client->GovernmentID[i] != '\n')
			// {
			// 	i++;
			// }

			// client->GovernmentID[i] = client->GovernmentID[i + 1];
			// i = 0;

			// printf("Please enter your Date of Travel: \n");
			// fgets(client->DateOfTravel, sizeof(client->DateOfTravel), stdin);

			// while(client->DateOfTravel[i] != '\n')
			// {
			// 	i++;
			// }

			// client->DateOfTravel[i] = client->DateOfTravel[i + 1];
			// i = 0;

			// printf("Please enter the number of travelers: \n");
			// fgets(client->NumberOfTravelers, sizeof(client->NumberOfTravelers), stdin);

			// while(client->NumberOfTravelers[i] != '\n')
			// {
			// 	i++;
			// }

			// client->NumberOfTravelers[i] = client->NumberOfTravelers[i + 1];
			// i = 0;


			printf("Please confirm your information: \n");
			printf("%s\n", c.ClientName);
			// printf("%s\n", c.DateOfBirth);
			// printf("%s\n", c.Gender);
			// printf("%d\n", c.GovernmentID);
			// printf("%s\n", c.DateOfTravel);
			// printf("%d\n", c.NumberOfTravelers);
		}

		if(strcmp(client->MenuOption, "2") == 0)
		{
			system("clear");
			printf("Inquiry about your ticket. \n");
			fgets(client->ClientName, sizeof(client->ClientName), stdin);
		}

		else if(strcmp(client->MenuOption, "3") == 0)
		{
			system("clear");
			printf("Modify your reservation. \n");
			fgets(client->ClientName, sizeof(client->ClientName), stdin);
		}

		else if(strcmp(client->MenuOption, "4") == 0)
		{
			system("clear");
			printf("Cancel your reservation. \n");
			fgets(client->ClientName, sizeof(client->ClientName), stdin);
		}

		else if(strcmp(client->MenuOption, "5") == 0)
		{
			exit(0);
		}


	}
}