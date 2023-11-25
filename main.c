#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char run;
    printf("\nWelcome to TravInfo with Group 7. (Demo)\n");
    printf("This program will provide information about travel routes in Germany\n");
    printf("and display indepth details about the best route for you based on your preferences.\n");
    printf("Follow the provided steps below with 5 being the best and 1 being worst.\n");
    while (1)
    {
        do
        {
            printf("\ns to start, q to quit: ");
            scanf(" %c", &run);
        } while (run != 's' && run != 'q');

        if (run == 'q')
        {
            break;
        }

        char startDestination[100];
        char endDestination[100];
        int co2_rating, time_rating, price_rating;
        int airplaneSize = 0, trainSize = 0;

        getNumberOfLines(&airplaneSize, &trainSize);

        Traveloption *airplanes_array = malloc(airplaneSize * sizeof(Traveloption));
        Traveloption *trains_array = malloc(trainSize * sizeof(Traveloption));

        int train_index1 = -1, train_index2 = -1, train_index3 = -1, airplane_index1 = -1, airplane_index2 = -1, airplane_index3 = -1;

        scan_user_input(&co2_rating, &time_rating, &price_rating, startDestination, endDestination);

        csv_read(airplanes_array, trains_array);

        // handle if it fails
        if (airplanes_array == NULL || trains_array == NULL)
        {
            return 1;
        }

        Traveloption *trains = find_route(trains_array, startDestination, endDestination, trainSize, &train_index1, &train_index2, &train_index3, TRAIN);

        Traveloption *airplanes = find_route(airplanes_array, startDestination, endDestination, airplaneSize, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

        Traveloption topTrain[] = {trains[train_index1], trains[train_index2], trains[train_index3]};
        Traveloption topAirplanes[] = {airplanes[airplane_index1], airplanes[airplane_index2], airplanes[airplane_index3]};

        // test til at hente data fra arraysne
        printf("%s - %s\n", airplanes[airplane_index1].startDest, airplanes[airplane_index1].endDest);

        printRoutes(topTrain, topAirplanes, co2_rating, price_rating, time_rating);

        free(airplanes_array);
        free(trains_array);
    }

    return 0;
}