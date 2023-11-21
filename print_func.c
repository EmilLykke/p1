#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int compare(const void *, const void *);
void rank_by_parameter(int, int, int,
                       int, int, int, int *,
                       int *, int *, int *, int *, int *);
void calculate_score(Traveloption *, Traveloption *, int, int, int,
                     int, int, int, int *, int *, int *,
                     int *, int *, int *, int, int, int);

void printRoutes(Traveloption *trains, Traveloption *flights, int train_index1, int train_index2, int train_index3, int airplane_index1, int airplane_index2, int airplane_index3, int co2_pref, int price_pref, int totalTime_pref)
{
    int train_score1, train_score2, train_score3, airplane_score1, airplane_score2, airplane_score3;

    // Print separator line
    printf("Trains \t\t\t");
    printf("Airplanes \n");
    // printf("|------------|-----------------|--------| \t\t\t");

    printf("|------------|-----------------|--------| \t\t\t");
    printf("|------------|-----------------|--------|\n");

    calculate_score(trains, flights, airplane_index1, airplane_index2, airplane_index3, train_index1, train_index2, train_index3, &airplane_score1, &airplane_score2, &airplane_score3, &train_score1, &train_score2, &train_score3, co2_pref, price_pref, totalTime_pref);
    // Print table rows
    printf("| %-10s | %-15s | %-6s | \t\t\t", "Score:", "Index", "Rank");
    printf("| %-10s | %-15s | %-6s | \n", "Score:", "Index", "Rank");
    printf("|------------|-----------------|--------|\n");
    printf("| %-10d | %-15d | %-6s |\n", train_score3, airplane_index3, "1");
    printf("| %-10d | %-15d | %-6s |\n", train_score1, train_index1, "2");
    printf("| %-10d | %-15d | %-6s |\n", airplane_score2, airplane_index2, "3");
}

void calculate_score(Traveloption *train, Traveloption *airplane, int airplane_index1, int airplane_index2, int airplane_index3,
                     int train_index1, int train_index2, int train_index3, int *airplane_score1, int *airplane_score2, int *airplane_score3,
                     int *train_score1, int *train_score2, int *train_score3, int co2_pref, int price_pref, int totalTime_pref)
{
    int temp_air_score1, temp_air_score2, temp_air_score3, temp_train_score1, temp_train_score2, temp_train_score3;

    // Total time
    rank_by_parameter(train[train_index1].totalTime, train[train_index2].totalTime, train[train_index3].totalTime, airplane[airplane_index1].totalTime, airplane[airplane_index2].totalTime,
                      airplane[airplane_index3].totalTime, &temp_air_score1, &temp_air_score2, &temp_air_score3, &temp_train_score1, &temp_train_score2, &temp_train_score3);

    *airplane_score1 = temp_air_score1 * totalTime_pref;
    *airplane_score2 = temp_air_score2 * totalTime_pref;
    *airplane_score3 = temp_air_score3 * totalTime_pref;

    printf("1: %d 2: %d 3: %d\n", *airplane_score1, *airplane_score2, *airplane_score3);

    *train_score1 = temp_train_score1 * totalTime_pref;
    *train_score2 = temp_train_score2 * totalTime_pref;
    *train_score3 = temp_train_score3 * totalTime_pref;

    // Price
    rank_by_parameter(train[train_index1].price, train[train_index2].price, train[train_index3].price, airplane[airplane_index1].price, airplane[airplane_index2].price,
                      airplane[airplane_index3].price, &temp_air_score1, &temp_air_score2, &temp_air_score3, &temp_train_score1, &temp_train_score2, &temp_train_score3);

    *airplane_score1 += temp_air_score1 * price_pref;
    *airplane_score2 += temp_air_score2 * price_pref;
    *airplane_score3 += temp_air_score3 * price_pref;

    *train_score1 += temp_train_score1 * price_pref;
    *train_score2 += temp_train_score2 * price_pref;
    *train_score3 += temp_train_score3 * price_pref;

    // CO2
    *airplane_score1 += 1 * co2_pref;
    *airplane_score2 += 1 * co2_pref;
    *airplane_score3 += 1 * co2_pref;

    *train_score1 += 6 * co2_pref;
    *train_score2 += 6 * co2_pref;
    *train_score3 += 6 * co2_pref;
}

void rank_by_parameter(int air_parametre1, int air_parametre2, int air_parametre3,
                       int train_parametre1, int train_parametre2, int train_parametre3, int *airplane_score1,
                       int *airplane_score2, int *airplane_score3, int *train_score1, int *train_score2, int *train_score3)
{
    int *ranking = (int *)malloc(6 * sizeof(int));
    ranking[0] = air_parametre1;
    ranking[1] = air_parametre2;
    ranking[2] = air_parametre3;
    ranking[3] = train_parametre1;
    ranking[4] = train_parametre2;
    ranking[5] = train_parametre3;

    qsort(ranking, 6, sizeof(int), compare);

    int air1 = 0, air2 = 0, air3 = 0;
    int train1 = 0, train2 = 0, train3 = 0;

    for (int i = 0; i < 6; i++)
    {
        if (air_parametre1 == ranking[i])
        {
            if (air1 == 0)
            {
                air1 = 6 + 1 - (i + 1);
            }
            // 6 number of travel options
            printf("air 1\n");
        }
        else if (air_parametre2 == ranking[i])
        {
            if (air2 == 0)
            {
                air2 = 6 + 1 - (i + 1);
            }
            printf("air 2\n");
        }
        else if (air_parametre3 == ranking[i])
        {
            if (air3 == 0)
            {
                air3 = 6 + 1 - (i + 1);
            }
            printf("air 3\n");
        }
        else if (train_parametre1 == ranking[i])
        {
            if (train1 == 0)
            {
                train1 = 6 + 1 - (i + 1);
            }
            printf("train 1\n");
        }
        else if (train_parametre2 == ranking[i])
        {
            if (train2 == 0)
            {
                train2 = 6 + 1 - (i + 1);
            }
            printf("train 2\n");
        }
        else if (train_parametre3 == ranking[i])
        {
            if (train3 == 0)
            {
                train3 = 6 + 1 - (i + 1);
            }
            printf("train 3\n");
        }
    }
    *airplane_score1 = air1;
    *airplane_score2 = air2;
    *airplane_score3 = air3;

    *train_score1 = train1;
    *train_score2 = train2;
    *train_score3 = train3;

    free(ranking);
}

int compare(const void *ip1, const void *ip2)
{
    int *ipi1, *ipi2;
    ipi1 = (int *)ip1;
    ipi2 = (int *)ip2;
    if (*ipi1 < *ipi2)
    {
        return -1;
    }
    else if (*ipi2 < *ipi1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}