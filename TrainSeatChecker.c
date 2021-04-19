 //Author: Ben Welch

 #include "functions.h"
 #include "structs.h"

int seatChecker()
{
   FILE *fp ;
   char c;
   int zeros = 0;


   printf( "Opening the file train in read mode \n" ) ;
   fp = fopen ( "train", "r" ) ; // opening an existing file
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