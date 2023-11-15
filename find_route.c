#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>

void find_route(struct traveloption *, char, char, int, int *, int *, int *, int); // three int pointers which are the three indexes
void calculate_option(struct traveloption *, int, int, int, int);

/* struct traveloption
{
    char startDest[100];
    char endDest[100];
    int traveltime;
    int price;
    int co2;
    double distance;
    int wastetime;
    int totaltime;

}; */

void find_route(struct traveloption *airplane_or_train_option, char input_startdestination, char input_enddestination,
                int size, int *index1, int *index2, int *index3, int case)
{
    int newtime, time1 = INT_MAX, time2 = INT_MAX, time3 = INT_MAX;

    // int size = sizeof(airplane_or_train_option) / sizeof(airplane_or_train_option[0]); // calculates size of  array

    for (int i = 0; i < size; i++)
    {
        if (strcmp(airplane_or_train_option[i].startDest, input_startdestination) == 0 && strcmp(airplane_or_train_option[i].endDest, input_enddestination) == 0)
        {

            newtime = airplane_or_train_option[i].traveltime;

            while (1)
            {
                if (newtime < time1)
                {

                    if (newtime < time2)
                    {
                        if (newtime < time3)
                        {
                            newtime = time3;
                            *index3 = i;
                            break;
                        }

                        newtime = time2;
                        *index2 = i;
                        break;
                    }

                    newtime = time1;
                    *index1 = i;
                    break;
                }
            }
        }
    }

    calculate_option(airplane_or_train_option, index1, index2, index3, case); // index 3 quickest, 2 2nd and index 1 is the slowest.
}

calculate_option(struct traveloption *airplane_or_train_option, int index1, int index2, int index3, int case) // måske index1,2,3 pointer?
{

    if (case == AIRPLANE)
    {
        // Calculates CO2 emmesion
        airplane_or_train_option[index1].co2 = airplane_or_train_option[index1].distance * 246; // 246 grams of CO2 per KM on average for airplanes. (Figur 3)
        airplane_or_train_option[index2].co2 = airplane_or_train_option[index2].distance * 246;
        airplane_or_train_option[index3].co2 = airplane_or_train_option[index3].distance * 246;

        airplane_or_train_option[index1].wastetime = 165; // 165 minutes averaged on downtime for airplanes.
        airplane_or_train_option[index2].wastetime = 165;
        airplane_or_train_option[index3].wastetime = 165;

        airplane_or_train_option[index1].totaltime = airplane_or_train_option[index1].wastetime + airplane_or_train_option[index1].traveltime; // traveltime + downtime
        airplane_or_train_option[index2].totaltime = airplane_or_train_option[index2].wastetime + airplane_or_train_option[index2].traveltime;
        airplane_or_train_option[index3].totaltime = airplane_or_train_option[index3].wastetime + airplane_or_train_option[index3].traveltime;
    }

    else if (case == TRAIN)
    {
        airplane_or_train_option[index1].co2 = airplane_or_train_option[index1].distance * 0; // 0 grams of CO2 per KM in German trains. ()
        airplane_or_train_option[index2].co2 = airplane_or_train_option[index2].distance * 0;
        airplane_or_train_option[index3].co2 = airplane_or_train_option[index3].distance * 0;

        airplane_or_train_option[index1].wastetime = 20; // average wastetime for train
        airplane_or_train_option[index2].wastetime = 20;
        airplane_or_train_option[index3].wastetime = 20;

        airplane_or_train_option[index1].totaltime = airplane_or_train_option[index1].wastetime + airplane_or_train_option[index1].traveltime; // traveltime + downtime
        airplane_or_train_option[index2].totaltime = airplane_or_train_option[index2].wastetime + airplane_or_train_option[index2].traveltime;
        airplane_or_train_option[index3].totaltime = airplane_or_train_option[index3].wastetime + airplane_or_train_option[index3].traveltime;
    }
}
