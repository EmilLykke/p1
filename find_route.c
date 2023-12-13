
// -----------------------------------------------------------------
//
//  File: find_route.c
//
//  History: Dec-6-23
//
//------------------------------------------------------------------

#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

Traveloption *calculate_option(Traveloption *, int, int *, int *, int *, int);

Traveloption *find_route(Traveloption *airplane_or_train_option, char *input_startDestination, char *input_endDestination,
                         int size, int *index1, int *index2, int *index3, int option)
{
    int newtime, time1 = INT_MAX, time2 = INT_MAX, time3 = INT_MAX;

    for (int i = 0; i < size; i++)
    {
        // Checks if any routes from the csv files matches with the user's input
        if (strcmp(airplane_or_train_option[i].startDest, input_startDestination) == 0 && strcmp(airplane_or_train_option[i].endDest, input_endDestination) == 0)
        {

            newtime = airplane_or_train_option[i].travelTime;

            // Is the found route's travel time the fastest -> assigns the index to index1
            if (newtime < time1 && newtime < time2 && newtime < time3)
            {
                *index3 = *index2;
                *index2 = *index1;
                *index1 = i;
                time3 = time2;
                time2 = time1;
                time1 = newtime;
            }

            // Is the found route's travel time the 2nd fastest -> assigns the index to index2
            else if (newtime >= time1 && newtime < time2 && newtime < time3)
            {
                *index3 = *index2;
                *index2 = i;
                time3 = time2;
                time2 = newtime;
            }
            // Is the found route's travel time the 3rd fastest -> assigns the index to index3
            else if (newtime >= time2 && newtime < time3)
            {
                *index3 = i;
                time3 = newtime;
            }
        }
    }

    //
    // Calculates CO2 emessions, waste time, and total time for the found routes.
    //

    airplane_or_train_option = calculate_option(airplane_or_train_option, size, index1, index2, index3, option);

    return airplane_or_train_option;
}

Traveloption *calculate_option(Traveloption *airplane_or_train_option, int size, int *index1, int *index2, int *index3, int option)
{
    // Allocates memoy for tempArr and copying the memory from the travel array into tempArr.
    Traveloption *tempArr = malloc(sizeof(Traveloption) * size);
    memcpy(tempArr, airplane_or_train_option, sizeof(Traveloption) * size);

    //
    // Calculations seen below
    //

    if (option == AIRPLANE)
    {
        // Calculates CO2 emmesion
        tempArr[*index1].co2 = tempArr[*index1].distance * 246.; // 246 grams of CO2 per KM on average for airplanes
        tempArr[*index2].co2 = tempArr[*index2].distance * 246.;
        tempArr[*index3].co2 = tempArr[*index3].distance * 246.;

        // Sets wastetime to 240 min (airplane)
        tempArr[*index1].wasteTime = 240;
        tempArr[*index2].wasteTime = 240;
        tempArr[*index3].wasteTime = 240;

        // Calculates totaltime= traveltime + downtime
        tempArr[*index1].totalTime = tempArr[*index1].wasteTime + tempArr[*index1].travelTime;
        tempArr[*index2].totalTime = tempArr[*index2].wasteTime + tempArr[*index2].travelTime;
        tempArr[*index3].totalTime = tempArr[*index3].wasteTime + tempArr[*index3].travelTime;
    }

    else if (option == TRAIN)
    {
        // Calculates grams of co2 per km for trains
        tempArr[*index1].co2 = tempArr[*index1].distance * 0.; // German trains entail 0 gram of CO2 pr KM
        tempArr[*index2].co2 = tempArr[*index2].distance * 0.;
        tempArr[*index3].co2 = tempArr[*index3].distance * 0.;

        // Sets wastetime to 35 min (train)
        tempArr[*index1].wasteTime = 35;
        tempArr[*index2].wasteTime = 35;
        tempArr[*index3].wasteTime = 35;

        // Calculates totaltime = travelTime + downtime
        tempArr[*index1].totalTime = tempArr[*index1].wasteTime + tempArr[*index1].travelTime;
        tempArr[*index2].totalTime = tempArr[*index2].wasteTime + tempArr[*index2].travelTime;
        tempArr[*index3].totalTime = tempArr[*index3].wasteTime + tempArr[*index3].travelTime;
    }

    return tempArr;
}
