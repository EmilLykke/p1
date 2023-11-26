#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void scanLine(char *, Traveloption *, int, int);

Traveloption *csv_read(char *filename, int *size, int type)
{
    char line[1024];
    // opens file
    FILE *stream = fopen(filename, "r");
    if (stream == NULL)
    {
        printf("Failed to open: %s", filename);
        exit(EXIT_FAILURE);
    }

    int m = 0;

    while (fgets(line, sizeof(line), stream))
    {
        m++;
    }

    *size = m - 1;

    Traveloption *airplane_or_train_array = (Traveloption *)malloc((*size) * sizeof(Traveloption));

    rewind(stream);

    int i = 0;
    // Read lines of airplanes file
    while (fgets(line, sizeof(line), stream))
    {
        if (i != 0)
        {
            scanLine(line, airplane_or_train_array, type, i - 1);
        }
        i++;
    }

    fclose(stream);

    return airplane_or_train_array;
}

void scanLine(char *line, Traveloption *arr, int type, int index)
{

    // Memory is allocated for the start and end dest
    // Due to the fact that the struct has defined start and end dest as char *
    arr[index].startDest = (char *)malloc(100);
    arr[index].endDest = (char *)malloc(100);

    sscanf(line, "%[^;];%[^;];%d;%lf;%lf;", arr[index].startDest, arr[index].endDest, &arr[index].travelTime, &arr[index].price, &arr[index].distance);

    // Sets the score and rank for later use
    arr[index].score = 0;
    arr[index].rank = 0;

    // Set type
    arr[index].type = type;
}
