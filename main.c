#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char startDestination[100];
    char endDestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers, size;
    Traveloption *flights_array;
    Traveloption *trains_array;
    int train_index1 = -1, train_index2 = -1, train_index3 = -1, airplane_index1 = -1, airplane_index2 = -1, airplane_index3 = -1;

    // scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, startdestination, enddestination);
    csv_read(&flights_array, &trains_array);

    // handle if it fails
    if (flights_array == NULL || trains_array == NULL)
    {
        return 1;
    }

    size = sizeof(trains_array) / sizeof(trains_array[0]);
    find_route(trains_array, startDestination, endDestination, size, &train_index1, &train_index2, &train_index3, TRAIN);

    size = sizeof(flights_array) / sizeof(flights_array[0]);
    find_route(flights_array, startDestination, endDestination, size, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

    // test til at hente data fra arraysne
    printf("%s - %s\n", flights_array[airplane_index1].startDest, flights_array[airplane_index1].endDest);

    free(flights_array);
    free(trains_array);

    return 0;
}