 //Author: Ben Welch

 #include "structs.h"
 #include "functions.h"

int seatChecker(int trainNum)
{
   FILE *fp ;
   char c;
   int zeros = 0;


   printf( "Opening the file train in read mode \n" ) ;
   if (trainNum == 0)
   {
       fp = fopen ( "train1", "r" ) ; // opening an existing file
   }
   else if (trainNum == 1)
   {
       fp = fopen ( "train2", "r" ) ; // opening an existing file
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
