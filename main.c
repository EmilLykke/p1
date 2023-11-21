#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char startDestination[100];
    char endDestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers;
    Traveloption *flights_array;
    Traveloption *trains_array;
    int train_index1 = -1, train_index2 = -1, train_index3 = -1, airplane_index1 = -1, airplane_index2 = -1, airplane_index3 = -1;
    int flightSize = 0, trainSize = 0;

    scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, startDestination, endDestination);
    csv_read(&flights_array, &trains_array, &flightSize, &trainSize);

    // handle if it fails
    if (flights_array == NULL || trains_array == NULL)
    {
        return 1;
    }

    Traveloption *trains = find_route(trains_array, startDestination, endDestination, trainSize, &train_index1, &train_index2, &train_index3, TRAIN);

    Traveloption *flights = find_route(flights_array, startDestination, endDestination, flightSize, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

    // test til at hente data fra arraysne
    printf("%s - %s\n", flights[airplane_index1].startDest, flights[airplane_index1].endDest);

    printRoutes(trains, flights, train_index1, train_index2, train_index3, airplane_index1, airplane_index2, airplane_index3, co2_rating, price_rating, time_rating);

    free(flights_array);
    free(trains_array);

    return 0;
}