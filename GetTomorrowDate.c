 //Author: Ben Welch

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int GetTomorrowDate(char *tomorrowsDate)
{
    FILE *fp;


    // variables to store the date and time components
    int hours, minutes, seconds, day, month, year;

    // `time_t` is an arithmetic time type
    time_t now = (int)time(NULL) + 86400;

    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after a minute (0-59)

    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;      // get month of year (0 to 11)
    year = local->tm_year + 1900;   // get year since 1900

    fp = fopen("dates.txt", "w+");

    // print the current date
    fprintf(fp, "%02d/%02d/%d", month, day, year);
    fclose(fp);

    fp = fopen("dates.txt", "r");

    fgets(tomorrowsDate, 11, fp);
    printf("%s", tomorrowsDate);
    fclose(fp);


    return 0;
}
