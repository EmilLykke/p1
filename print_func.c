
// -----------------------------------------------------------------
//
//  File: print_func.c
//
//  History: Dec-10-23
//
//------------------------------------------------------------------

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int sortTotalTime(const void *, const void *);
int sortPrice(const void *, const void *);
int sortCo2(const void *, const void *);
int sortScore(const void *, const void *);
void setRank(Traveloption *, int);
char optionLetter(int);

void rank_by_param(Traveloption *, Traveloption *, int, int, int, int);
void calcualte_score(Traveloption *, Traveloption *, int, int, int);
char *convertMinutesToHours(int);

void printRoutes(Traveloption *trains, Traveloption *airplanes, int co2_pref, int price_pref, int totalTime_pref)
{
    // Sets rank and calculates score of our found routes
    calcualte_score(trains, airplanes, co2_pref, price_pref, totalTime_pref);

    printf("\n\n\nThe table below displays options A, B, and C for each travel mode (airplane or train option) leading to your destination.\nEach route is ranked from 1 to 6 and is detailed with information regarding its parameters.\nStill confused? Press 'h' below");

    // Print headers
    printf("\n\n ╔════════════════════════════════════════════════╦═════════════════════════════════════════════╗\n");
    printf(" ║ Trains                                         ║ Airplanes                                   ║\n");
    printf(" ╠════════════════════════════════════════════════╬═════════════════════════════════════════════╣\n");

    // Print table rows
    for (int i = 0; i < 3; i++)
    {
        char *trainTrav = convertMinutesToHours(trains[i].travelTime);
        char *trainDown = convertMinutesToHours(trains[i].wasteTime);
        char *trainTotal = convertMinutesToHours(trains[i].totalTime);

        char *airplaneTrav = convertMinutesToHours(airplanes[i].travelTime);
        char *airplaneDown = convertMinutesToHours(airplanes[i].wasteTime);
        char *airplaneTotal = convertMinutesToHours(airplanes[i].totalTime);

        printf(" ║                   Option %c                     ║                    Option %c                 ║\n", optionLetter(i), optionLetter(i));
        printf(" ║ Rank: %-10d                               ║ Rank: %-10d                            ║\n", trains[i].rank, airplanes[i].rank);
        printf(" ║ Score: %-10.2lf                              ║ Score: %-10.2lf                           ║\n", trains[i].score, airplanes[i].score);
        printf(" ║                                                ║                                             ║\n");
        printf(" ║ CO2 (grams): %-21.2lf             ║ CO2 (grams): %-21.1lf          ║\n", trains[i].co2, airplanes[i].co2);
        printf(" ║ Travel Time: %-18s                ║ Travel Time: %-18s             ║\n", convertMinutesToHours(trains[i].travelTime), convertMinutesToHours(airplanes[i].travelTime));
        printf(" ║ Down Time: %-18s                  ║ Down Time: %-18s               ║\n", convertMinutesToHours(trains[i].wasteTime), convertMinutesToHours(airplanes[i].wasteTime));
        printf(" ║ Total Time: %-10s                 ║ Total Time: %-10s              ║\n", convertMinutesToHours(trains[i].totalTime), convertMinutesToHours(airplanes[i].totalTime));
        printf(" ║ Price (euros): %-13.2lf                   ║ Price (euros): %-13.2lf                ║\n", trains[i].price, airplanes[i].price);
        printf(" ╠════════════════════════════════════════════════╬═════════════════════════════════════════════╣\n");

        // Frees memory
        free(trainTrav);
        free(trainDown);
        free(trainTotal);
        free(airplaneTrav);
        free(airplaneDown);
        free(airplaneTotal);
    }

    // Bottom line
    printf(" ╚════════════════════════════════════════════════╩═════════════════════════════════════════════╝\n");
}

void calcualte_score(Traveloption *trains, Traveloption *airplanes, int co2_pref, int price_pref, int totalTime_pref)
{

    //
    // Ranks traveloption for trains and airplaine aswell as calculate scores
    //

    rank_by_param(trains, airplanes, co2_pref, price_pref, totalTime_pref, 0);

    rank_by_param(trains, airplanes, co2_pref, price_pref, totalTime_pref, 1);

    rank_by_param(trains, airplanes, co2_pref, price_pref, totalTime_pref, 2);
}

void rank_by_param(Traveloption *trains, Traveloption *airplanes, int co2_pref, int price_pref, int totalTime_pref, int type)
{
    // Allocates memory
    Traveloption *ranking = (Traveloption *)malloc(6 * sizeof(Traveloption));

    // Init our found routes to a ranking array
    ranking[0] = trains[0];
    ranking[1] = trains[1];
    ranking[2] = trains[2];
    ranking[3] = airplanes[0];
    ranking[4] = airplanes[1];
    ranking[5] = airplanes[2];

    // Type 0 = ranks total time
    if (type == 0)
    {
        // sort the array based on totalTime
        qsort(ranking, 6, sizeof(Traveloption), sortTotalTime);

        for (int i = 0; i < 6; i++)
        {
            // set the ranks for each element when looking at totalTime
            setRank(ranking, 0);
        }

        for (int i = 0; i < 6; i++)
        {
            // calculate the score based on rank and multiply by preference for each element.
            // Add to element score
            ranking[i].score += (6 + 1 - (ranking[i].rank)) * totalTime_pref;
        }
    }

    // Type 1 = ranks price
    else if (type == 1)
    {
        // sort the array based on price
        qsort(ranking, 6, sizeof(Traveloption), sortPrice);

        for (int i = 0; i < 6; i++)
        {
            // set the ranks for each element when looking at price
            setRank(ranking, 1);
        }

        for (int i = 0; i < 6; i++)
        {
            // calculate the score based on rank and multiply by preference for each element.
            // Add to element score
            ranking[i].score += (6 + 1 - (ranking[i].rank)) * price_pref;
        }
    }

    // Type 2 = ranks co2
    else if (type == 2)
    {
        // sort the array based on co2
        qsort(ranking, 6, sizeof(Traveloption), sortCo2);

        for (int i = 0; i < 6; i++)
        {
            // set the ranks for each element when looking at co2
            setRank(ranking, 2);
        }

        for (int i = 0; i < 6; i++)
        {
            // calculate the score based on rank and multiply by preference for each element.
            // Add to element score
            ranking[i].score += (6 + 1 - (ranking[i].rank)) * co2_pref;
        }
    }

    // sort the array based on score
    qsort(ranking, 6, sizeof(Traveloption), sortScore);

    // set the ranks for each element when looking at score
    setRank(ranking, 3);

    int airIn = 0, trainIn = 0;

    // Replace the old elemetns in trains and airplanes array with new elements with calculated scores.
    for (int i = 0; i < 6; i++)
    {
        if (ranking[i].type == TRAIN)
        {
            trains[trainIn] = ranking[i];
            trainIn++;
        }
        else if (ranking[i].type == AIRPLANE)
        {

            airplanes[airIn] = ranking[i];
            airIn++;
        }
    }

    // free the memory for the ranking array
    free(ranking);
}

int sortTotalTime(const void *ip1, const void *ip2)
{
    Traveloption *ipi1, *ipi2;
    ipi1 = (Traveloption *)ip1;
    ipi2 = (Traveloption *)ip2;

    // Sort by accending, meaning from smallest to largest
    if (ipi1->totalTime < ipi2->totalTime)
    {
        return -1;
    }
    else if (ipi2->totalTime < ipi1->totalTime)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int sortPrice(const void *ip1, const void *ip2)
{
    Traveloption *ipi1, *ipi2;
    ipi1 = (Traveloption *)ip1;
    ipi2 = (Traveloption *)ip2;

    // Sort by accending, meaning from smallest to largest
    if (ipi1->price < ipi2->price)
    {
        return -1;
    }
    else if (ipi2->price < ipi1->price)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int sortCo2(const void *ip1, const void *ip2)
{
    Traveloption *ipi1, *ipi2;
    ipi1 = (Traveloption *)ip1;
    ipi2 = (Traveloption *)ip2;

    // Sort by accending, meaning from smallest to largest
    if (ipi1->co2 < ipi2->co2)
    {
        return -1;
    }
    else if (ipi2->co2 < ipi1->co2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int sortScore(const void *ip1, const void *ip2)
{
    Traveloption *ipi1, *ipi2;
    ipi1 = (Traveloption *)ip1;
    ipi2 = (Traveloption *)ip2;

    // Sort by decending, meaning from largest to smallest
    if (ipi1->score > ipi2->score)
    {
        return -1;
    }
    else if (ipi2->score > ipi1->score)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void setRank(Traveloption *arr, int type)
{
    // Assign ranks to each element in array
    for (int i = 0; i < 6; i++)
    {
        arr[i].rank = i + 1;
    }

    // Adjust ranks for equal scores based on time, price, and co2 preferences
    // Chekcing for equal values in the array.
    for (int i = 0; i < 6; i++)
    {
        if (arr[i].score == arr[i + 1].score)
        {
            // type 0 is totalTime
            if (type == 0)
            {
                // If two elements have same time, assign the same rank
                if (arr[i].totalTime == arr[i + 1].totalTime)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
            // type 1 is price
            else if (type == 1)
            {
                // If two elements have same price, assign the same rank
                if (arr[i].price == arr[i + 1].price)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
            // type 2 is co2
            else if (type == 2)
            {
                // If two elements have same co2, assign the same rank
                if (arr[i].co2 == arr[i + 1].co2)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
            // else is score
            else
            {
                // If two elements have same score, assign the same rank
                if (arr[i].score == arr[i + 1].score)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
        }
    }
}

char optionLetter(int i)
{
    switch (i)
    {
    case 0:
        return 'A';
        break;
    case 1:
        return 'B';
        break;
    case 2:
        return 'C';
        break;

    default:
        break;
    }
}

// Function for converting minutes to minutes and hours
char *convertMinutesToHours(int time)
{
    // ints for hours and mins
    int hours, minutes;

    // string containing hours and minutes
    char *final = (char *)malloc(50);

    // calculations
    hours = time / 60;
    minutes = time % 60;

    // check if there is any hours
    if (hours < 1)
    {
        // sprintf to print a format string to the string variable final
        sprintf(final, "%d minutes", minutes);
    }
    else
    {
        // sprintf to print a format string to the string variable final
        sprintf(final, "%d hours %d minutes", hours, minutes);
    }

    // return final string
    return final;
}
