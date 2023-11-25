#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void scanLine(char *, Traveloption *, int, int);

void csv_read(Traveloption *airplanes_array, Traveloption *trains_array)
{
    char line[1024];
    // opens airplanes file
    FILE *stream = fopen("airplanes.csv", "r");

    // Read lines of airplanes file
    int i = 0;
    while (fgets(line, 1024, stream))
    {
        if (i != 0)
        {
            scanLine(line, airplanes_array, AIRPLANE, i - 1);
        }
        i++;
    }
    fclose(stream);

    // opens trains file
    stream = fopen("trains.csv", "r");
    i = 0;
    while (fgets(line, 1024, stream))
    {
        if (i != 0)
        {
            scanLine(line, trains_array, TRAIN, i - 1);
        }
        i++;
    }
    fclose(stream);
}

void scanLine(char *line, Traveloption *arr, int type, int index)
{

    char start[100];
    char end[100];

    sscanf(line, " %[^;];%[^;];%d;%lf;%lf;", start, end, &arr[index].travelTime, &arr[index].price, &arr[index].distance);

    // Memory is allocated for the start and end dest
    // The string is copied into the item
    // Due to the fact that the struct has defined start and end dest as char *
    // and strings cannot be asigned directly
    arr[index].startDest = malloc(100);
    arr[index].endDest = malloc(100);
    strcpy(arr[index].startDest, start);
    strcpy(arr[index].endDest, end);

    // Sets the score and rank for later use
    arr[index].score = 0;
    arr[index].rank = 0;

    // Set type
    arr[index].type = type;
}

void getNumberOfLines(int *airplaneSize, int *trainSize)
{
    char line[1024];
    FILE *stream = fopen("airplanes.csv", "r");
    int i = 0;
    while (fgets(line, 1024, stream))
    {
        i++;
    }
    *airplaneSize = i - 1;

    stream = fopen("trains.csv", "r");
    i = 0;
    while (fgets(line, 1024, stream))
    {
        i++;
    }
    *trainSize = i - 1;
}