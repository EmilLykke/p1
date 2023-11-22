#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int sortTotalTime(const void *, const void *);
int sortPrice(const void *, const void *);
int sortScore(const void *, const void *);

void rank_by_param(Traveloption *, Traveloption *, int, int, int, int);
void calcualte_score(Traveloption *, Traveloption *, int, int, int);

void printRoutes(Traveloption *trains, Traveloption *airplanes, int co2_pref, int price_pref, int totalTime_pref)
{

    calcualte_score(trains, airplanes, co2_pref, price_pref, totalTime_pref);

    qsort(trains, 3, sizeof(Traveloption), sortScore);
    qsort(airplanes, 3, sizeof(Traveloption), sortScore);

    // Print headers
    printf("\n\n%-20c \t\t\t Travel options:\n", ' ');
    printf("Trains %-31c \t\t\t\t", ' ');
    printf("Airplanes \n");

    // Print separator line
    printf("|------------|-----------------|--------| \t\t\t");
    printf("|------------|-----------------|--------|\n");

    // Print table rows
    // Left header
    printf("| %-10s | %-15s | %-6s | \t\t\t", "Score:", "CO2", "Rank");
    // Right reader
    printf("| %-10s | %-15s | %-6s | \n", "Score:", "CO2", "Rank");

    // Left splitter
    printf("|------------|-----------------|--------| \t\t\t");
    // Right splitter
    printf("|------------|-----------------|--------|\n");

    // Left
    printf("| %-10d | %-15d | %-6s | \t\t\t", trains[0].score, trains[0].co2, "1");
    // Right
    printf("| %-10d | %-15d | %-6s |\n", airplanes[0].score, airplanes[0].co2, "1");

    // Left
    printf("| %-10d | %-15d | %-6s | \t\t\t", trains[1].score, trains[1].co2, "2");
    // Right
    printf("| %-10d | %-15d | %-6s |\n", airplanes[1].score, airplanes[1].co2, "2");

    // Left
    printf("| %-10d | %-15d | %-6s | \t\t\t", trains[2].score, trains[2].co2, "3");
    // Right
    printf("| %-10d | %-15d | %-6s |\n", airplanes[2].score, airplanes[2].co2, "3");
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
            ranking[i].score += (6 + 1 - (i + 1)) * totalTime_pref;
        }
    }
    // Type 1 = price
    else if (type == 1)
    {
        qsort(ranking, 6, sizeof(Traveloption), sortPrice);

        for (int i = 0; i < 6; i++)
        {
            ranking[i].score += (6 + 1 - (i + 1)) * totalTime_pref;
        }
    }
    // Type 2 = co2
    else if (type == 2)
    {
        for (int i = 0; i < 6; i++)
        {
            if (ranking[i].type == TRAIN)
            {
                ranking[i].score += 6 * co2_pref;
            }
            else if (ranking[i].type == AIRPLANE)
            {
                ranking[i].score += 1 * co2_pref;
            }
        }
    }

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
    if (ipi1->totalTime > ipi2->totalTime)
    {
        return -1;
    }
    else if (ipi2->totalTime > ipi1->totalTime)
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
    if (ipi1->price > ipi2->price)
    {
        return -1;
    }
    else if (ipi2->price > ipi1->price)
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