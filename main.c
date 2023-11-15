#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char startdestination[100];
    char enddestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers;
    Traveloption *flights_array = malloc(sizeof(Traveloption) * 15);
    Traveloption *trains_array = malloc(sizeof(Traveloption) * 15);

    // handle if it fails
    if (flights_array == NULL || trains_array == NULL)
    {
        return 1;
    }

    // scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, startdestination, enddestination);
    csv_read(&flights_array, &trains_array);

    // test til at hente data fra arraysne
    printf("%s \n", flights_array[1].startDest);

    free(flights_array);
    free(trains_array);

    return 0;
}