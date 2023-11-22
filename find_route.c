#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

Traveloption *calculate_option(Traveloption *, int *, int *, int *, int);

Traveloption *find_route(Traveloption *airplane_or_train_option, char *input_startDestination, char *input_endDestination,
                         int size, int *index1, int *index2, int *index3, int option)
{
    int newtime, time1 = INT_MAX, time2 = INT_MAX, time3 = INT_MAX;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(airplane_or_train_option[i].startDest, input_startDestination) == 0 && strcmp(airplane_or_train_option[i].endDest, input_endDestination) == 0)
        {

            newtime = airplane_or_train_option[i].travelTime;

            if (newtime < time1 && newtime < time2 && newtime < time3)
            {
                *index3 = *index2;
                *index2 = *index1;
                *index1 = i;
                time3 = time2;
                time2 = time1;
                time1 = newtime;
            }
            else if (newtime >= time1 && newtime < time2 && newtime < time3)
            {
                *index3 = *index2;
                *index2 = i;
                time3 = time2;
                time2 = newtime;
            }
            else if (newtime >= time2 && newtime < time3)
            {
                *index3 = i;
                time3 = newtime;
            }
        }
    }

    airplane_or_train_option = calculate_option(airplane_or_train_option, index1, index2, index3, option); // index 3 quickest, 2 2nd and index 1 is the slowest
    return airplane_or_train_option;
}

Traveloption *calculate_option(Traveloption *airplane_or_train_option, int *index1, int *index2, int *index3, int option) // måske index1,2,3 pointer?
{
    Traveloption *tempArr = malloc(sizeof(Traveloption) * 18);
    memcpy(tempArr, airplane_or_train_option, sizeof(Traveloption) * 18);

    if (option == AIRPLANE) // Præcise værdier skal ændres ud for rapporten. Særligt tag et kig på wasteTime
    {
        // Calculates CO2 emmesion
        tempArr[*index1].co2 = tempArr[*index1].distance * 246.; // 246 grams of CO2 per KM on average for airplanes (Figur 3)
        tempArr[*index2].co2 = tempArr[*index2].distance * 246.;
        tempArr[*index3].co2 = tempArr[*index3].distance * 246.;

        tempArr[*index1].wasteTime = 240; // 165 minutes averaged on downtime for airplanes
        tempArr[*index2].wasteTime = 240;
        tempArr[*index3].wasteTime = 240;

        tempArr[*index1].totalTime = tempArr[*index1].wasteTime + tempArr[*index1].travelTime; // travelTime + downtime
        tempArr[*index2].totalTime = tempArr[*index2].wasteTime + tempArr[*index2].travelTime;
        tempArr[*index3].totalTime = tempArr[*index3].wasteTime + tempArr[*index3].travelTime;
    }

    else if (option == TRAIN)
    {
        tempArr[*index1].co2 = tempArr[*index1].distance * 0.; // 0 grams of CO2 per KM in German trains ()
        tempArr[*index2].co2 = tempArr[*index2].distance * 0.;
        tempArr[*index3].co2 = tempArr[*index3].distance * 0.;

        tempArr[*index1].wasteTime = 35; // average wasteTime for train
        tempArr[*index2].wasteTime = 35;
        tempArr[*index3].wasteTime = 35;

        tempArr[*index1].totalTime = tempArr[*index1].wasteTime + tempArr[*index1].travelTime; // travelTime + downtime
        tempArr[*index2].totalTime = tempArr[*index2].wasteTime + tempArr[*index2].travelTime;
        tempArr[*index3].totalTime = tempArr[*index3].wasteTime + tempArr[*index3].travelTime;
    }

    return tempArr;
}
