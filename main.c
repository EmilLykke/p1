#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void printHelp();

int main(void)
{
    char run;
    printf("\n\nWelcome to TravInfo. (Demo)\n\n");
    printf("------------------------------------------------------------------\n");
    printf("This program will provide information about travel routes in Germany\n");
    printf("and display indepth details about the best route for you based on your preferences.\n");
    printf("Follow the provided steps below to see travel recomendations.\nFirstly you will be asked to declare how much you care about given parametres when choosing your travel form. \n");
    printf("Where 5 indicates high significance or strong emphasis, and 1 indicates low significance or minimal emphasis.");

    while (1)
    {
        do
        {
            printf("\n\nPress s to start, q to quit, press h for more help/info regarding the displayed table: ");
            scanf(" %c", &run);
        } while (run != 's' && run != 'q' && run != 'h');

        if (run == 'q')
        {
            break;
        }

        if (run == 'h')
        {
            printHelp();
        }

        char startDestination[100];
        char endDestination[100];
        int co2_rating, time_rating, price_rating;
        int train_index1 = -1, train_index2 = -1, train_index3 = -1, airplane_index1 = -1, airplane_index2 = -1, airplane_index3 = -1;

        scan_user_input(&co2_rating, &time_rating, &price_rating, startDestination, endDestination);

        int airplaneSize = 0, trainSize = 0;

        Traveloption *airplanes_array = csv_read("airplanes.csv", &airplaneSize, AIRPLANE);
        Traveloption *trains_array = csv_read("trains.csv", &trainSize, TRAIN);

        // handle if it fails
        if (airplanes_array == NULL || trains_array == NULL)
        {
            return 1;
        }

        Traveloption *airplanes = find_route(airplanes_array, startDestination, endDestination, airplaneSize, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

        Traveloption *trains = find_route(trains_array, startDestination, endDestination, trainSize, &train_index1, &train_index2, &train_index3, TRAIN);

        while (train_index1 == -1 || train_index2 == -1 || train_index3 == -1 || airplane_index1 == -1 || airplane_index2 == -1 || airplane_index3 == -1)
        {
            printf("\n\nNo route found, please try again\n");

            startpoint_and_destination(startDestination, endDestination);

            airplanes = find_route(airplanes_array, startDestination, endDestination, airplaneSize, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

            trains = find_route(trains_array, startDestination, endDestination, trainSize, &train_index1, &train_index2, &train_index3, TRAIN);
        }

        Traveloption topTrains[] = {trains[train_index1], trains[train_index2], trains[train_index3]};
        Traveloption topAirplanes[] = {airplanes[airplane_index1], airplanes[airplane_index2], airplanes[airplane_index3]};

        printRoutes(topTrains, topAirplanes, co2_rating, price_rating, time_rating);

        free(airplanes_array);
        free(trains_array);
        free(airplanes);
        free(trains);
    }

    return 0;
}

void printHelp()
{
    printf("\n\n------------------------------------------------------------------\n");
    printf("\nRank\n");
    printf("\n\t- The routes are ranked according to their given score\n\n");

    printf("Score (the higher the better)\n");
    printf("\n\t- The scoring system incorporates the information you've submitted within each category, calculating it against the personalized available routes.\n\t A higher score signifies a route better fitted to meet your preferences. The score is not out of 100 but should just be read as; the higher the better.\n\n");

    printf("CO2 (in grams per person per km)\n");
    printf("\n\t- The CO2 emissions are calculated by multiplying the average CO2 emissions per person per kilometer traveled for both trains and airplanes.\n\t The average CO2 emission per person per kilometer for trains is 0 grams, while for airplanes, it is 246 grams. (For context, people emit an average of 1.45 kg of CO2 per day.)\n");
    printf("\t- CO2 emissions are calculated based on the distance from the average emessions per person for an airplane.\n\n");

    printf("Travel time (in hours/minutes)\n");
    printf("\n\t- Travel time is the time spent on the actual airplane or traine ride.\n");

    printf("Down time (in hours/minutes)\n");
    printf("\n\t- Down time is the expected waiting time in the airport, the average delay for airplanes/trains, and your trip to the airport/station.\n");
    printf("\t- Down time is on average for airplanes 4 hours (240 minutes) and trains 35 minutes.\n\n");

    printf("Total time (in hours/minutes)\n");
    printf("\n\t- The total time is the travel time added with the down time.\n");

    printf("Price (in euro)\n");
    printf("\n\t- Shows the ticket price for the specific travel option in euros.\n\n");
    printf("------------------------------------------------------------------\n");
    printf("\n\n");
}
