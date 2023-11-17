#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

void calculate_option(Traveloption **, int *, int *, int *, int);

void find_route(Traveloption **airplane_or_train_option, char *input_startDestination, char *input_endDestination,
                int size, int *index1, int *index2, int *index3, int option)
{
    int newtime, time1 = INT_MAX, time2 = INT_MAX, time3 = INT_MAX;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(airplane_or_train_option[i]->startDest, input_startDestination) == 0 && strcmp(airplane_or_train_option[i]->endDest, input_endDestination) == 0)
        {

            newtime = airplane_or_train_option[i]->travelTime;

            while (1)
            {
                if (newtime < time1)
                {

                    if (newtime < time2)
                    {
                        if (newtime < time3)
                        {
                            newtime = time3;
                            *index1 = i;
                            break;
                        }

                        newtime = time2;
                        *index2 = i;
                        break;
                    }

                    newtime = time1;
                    *index3 = i;
                    break;
                }
            }
        }
    }

    calculate_option(airplane_or_train_option, index1, index2, index3, option); // index 3 quickest, 2 2nd and index 1 is the slowest
}

void calculate_option(Traveloption **airplane_or_train_option, int *index1, int *index2, int *index3, int option) // måske index1,2,3 pointer?
{
    Traveloption *tempArr = malloc(sizeof(Traveloption) * 15);
    memcpy(tempArr, *airplane_or_train_option, sizeof(Traveloption) * 15);

    if (option == AIRPLANE) // Præcise værdier skal ændres ud for rapporten-> Særligt tag et kig på wasteTime
    {
        // Calculates CO2 emmesion
        tempArr[*index1].co2 = airplane_or_train_option[*index1]->distance * 246; // 246 grams of CO2 per KM on average for airplanes (Figur 3)
        tempArr[*index2].co2 = airplane_or_train_option[*index2]->distance * 246;
        tempArr[*index3].co2 = airplane_or_train_option[*index3]->distance * 246;

        tempArr[*index1].wasteTime = 165; // 165 minutes averaged on downtime for airplanes
        tempArr[*index2].wasteTime = 165;
        tempArr[*index3].wasteTime = 165;

        tempArr[*index1].totalTime = airplane_or_train_option[*index1]->wasteTime + airplane_or_train_option[*index1]->travelTime; // travelTime + downtime
        tempArr[*index2].totalTime = airplane_or_train_option[*index2]->wasteTime + airplane_or_train_option[*index2]->travelTime;
        tempArr[*index3].totalTime = airplane_or_train_option[*index3]->wasteTime + airplane_or_train_option[*index3]->travelTime;
    }

    else if (option == TRAIN)
    {
        tempArr[*index1].co2 = airplane_or_train_option[*index1]->distance * 0; // 0 grams of CO2 per KM in German trains ()
        tempArr[*index2].co2 = airplane_or_train_option[*index2]->distance * 0;
        tempArr[*index3].co2 = airplane_or_train_option[*index3]->distance * 0;

        tempArr[*index1].wasteTime = 20; // average wasteTime for train
        tempArr[*index2].wasteTime = 20;
        tempArr[*index3].wasteTime = 20;

        tempArr[*index1].totalTime = airplane_or_train_option[*index1]->wasteTime + airplane_or_train_option[*index1]->travelTime; // travelTime + downtime
        tempArr[*index2].totalTime = airplane_or_train_option[*index2]->wasteTime + airplane_or_train_option[*index2]->travelTime;
        tempArr[*index3].totalTime = airplane_or_train_option[*index3]->wasteTime + airplane_or_train_option[*index3]->travelTime;
    }

    memcpy(*airplane_or_train_option, tempArr, sizeof(Traveloption) * 15);
    free(tempArr);
}
