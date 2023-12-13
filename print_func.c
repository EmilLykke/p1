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

    calcualte_score(trains, airplanes, co2_pref, price_pref, totalTime_pref);

    printf("\n\n\nThe table below displays options A, B, and C for each travel mode (airplane or train option) leading to your destination.\nEach route is ranked from 1 to 6 and is detailed with information regarding its parameters.\nStill confused? Press 'h' below");

    printf("\n\n ╔════════════════════════════════════════════════╦═════════════════════════════════════════════╗\n");
    // Print headers
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
        printf(" ║ CO2 (grams emitted/per person): %-8.2lf       ║ CO2 (grams emitted/per person): %-8.1lf    ║\n", trains[i].co2, airplanes[i].co2);
        printf(" ║ Travel Time: %-18s                ║ Travel Time: %-18s             ║\n", convertMinutesToHours(trains[i].travelTime), convertMinutesToHours(airplanes[i].travelTime));
        printf(" ║ Down Time: %-18s                  ║ Down Time: %-18s               ║\n", convertMinutesToHours(trains[i].wasteTime), convertMinutesToHours(airplanes[i].wasteTime));
        printf(" ║ Total Time: %-10s                 ║ Total Time: %-10s              ║\n", convertMinutesToHours(trains[i].totalTime), convertMinutesToHours(airplanes[i].totalTime));
        printf(" ║ Price (in euros): %-10.2lf                   ║ Price (in euros): %-10.2lf                ║\n", trains[i].price, airplanes[i].price);
        printf(" ╠════════════════════════════════════════════════╬═════════════════════════════════════════════╣\n");

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
    rank_by_param(trains, airplanes, co2_pref, price_pref, totalTime_pref, 0);

    rank_by_param(trains, airplanes, co2_pref, price_pref, totalTime_pref, 1);

    rank_by_param(trains, airplanes, co2_pref, price_pref, totalTime_pref, 2);
}

void rank_by_param(Traveloption *trains, Traveloption *airplanes, int co2_pref, int price_pref, int totalTime_pref, int type)
{
    Traveloption *ranking = (Traveloption *)malloc(6 * sizeof(Traveloption));
    ranking[0] = trains[0];
    ranking[1] = trains[1];
    ranking[2] = trains[2];
    ranking[3] = airplanes[0];
    ranking[4] = airplanes[1];
    ranking[5] = airplanes[2];

    // Type 0 = total time
    if (type == 0)
    {
        qsort(ranking, 6, sizeof(Traveloption), sortTotalTime);

        for (int i = 0; i < 6; i++)
        {
            setRank(ranking, 0);
        }

        for (int i = 0; i < 6; i++)
        {
            ranking[i].score += (6 + 1 - (ranking[i].rank)) * totalTime_pref;
        }
    }

    // Type 1 = price
    else if (type == 1)
    {
        qsort(ranking, 6, sizeof(Traveloption), sortPrice);

        for (int i = 0; i < 6; i++)
        {
            setRank(ranking, 1);
        }

        for (int i = 0; i < 6; i++)
        {
            ranking[i].score += (6 + 1 - (ranking[i].rank)) * price_pref;
        }
    }
    // Type 2 = co2
    else if (type == 2)
    {
        qsort(ranking, 6, sizeof(Traveloption), sortCo2);

        for (int i = 0; i < 6; i++)
        {
            setRank(ranking, 2);
        }

        for (int i = 0; i < 6; i++)
        {
            ranking[i].score += (6 + 1 - (ranking[i].rank)) * co2_pref;
        }
    }

    qsort(ranking, 6, sizeof(Traveloption), sortScore);
    setRank(ranking, 2);

    int airIn = 0, trainIn = 0;
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

    free(ranking);
}

int sortTotalTime(const void *ip1, const void *ip2)
{
    Traveloption *ipi1, *ipi2;
    ipi1 = (Traveloption *)ip1;
    ipi2 = (Traveloption *)ip2;
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
    // Assign ranks based on totalTime and price preferences
    for (int i = 0; i < 6; i++)
    {
        arr[i].rank = i + 1;
    }

    // Adjust ranks for equal scores based on time and price preferences
    for (int i = 0; i < 6; i++)
    {
        if (arr[i].score == arr[i + 1].score)
        {
            if (type == 0)
            {
                if (arr[i].totalTime == arr[i + 1].totalTime)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
            else if (type == 1)
            {
                if (arr[i].price == arr[i + 1].price)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
            else if (type == 2)
            {
                if (arr[i].co2 == arr[i + 1].co2)
                {
                    arr[i + 1].rank = arr[i].rank;
                }
            }
            else
            {
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

char *convertMinutesToHours(int time)
{
    // Ensure non-negative input
    int calchour;
    int restmin;
    char *final = (char *)malloc(50);

    calchour = time / 60;
    restmin = time % 60;

    if (calchour < 1)
    {
        sprintf(final, "%d minutes", restmin);
    }
    else
    {
        sprintf(final, "%d hours %d minutes", calchour, restmin);
    }

    return final;
}
