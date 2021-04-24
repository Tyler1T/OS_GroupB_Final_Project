 //Author: Ben Welch

#include "header.h"

int seatChecker(int trainNum)
{
   FILE *fp ;
   char c;
   int zeros = 0;

   printf( "Opening the file train in read mode \n" ) ;
   if (trainNum == 1)
   {
       fp = fopen ( "train1.txt", "r" ) ; // opening an existing file
   }
   else if (trainNum == 2)
   {
       fp = fopen ( "train2.txt", "r" ) ; // opening an existing file
   }
   if ( fp == NULL )
   {
     printf ( "Could not open file train \n" ) ;
     return 1;
   }
   printf( "Reading the file train \n" ) ;
   while ( 1 )
   {
     c = fgetc ( fp ) ; // reading the file

     if(c == '0')
     {
         zeros++;
         printf("%d\n", zeros);
     }

     if ( c == EOF )
     break ;
     //printf ( "%c", c );
   }
   printf("Closing the file train \n") ;
   fclose ( fp ) ; // Closing the file
   return zeros;
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
        } else break;
        output[char_index++] = ' ';
        count++;
        if ((count % 5) == 0) output[char_index++] = '\n';
    }
    printf("Closing the file train \n") ;
    fclose (fp) ; // Closing the file
    return;

}
