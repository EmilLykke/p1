#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Returns an array of the different sections of the string
char **splitString(char *line)
{
    char *tok = strtok(line, ";");
    int i = 0;
    char **array = (char **)malloc(8 * sizeof(char *));
    while (tok != NULL)
    {
        array[i] = strdup(tok);
        tok = strtok(NULL, ";");
        i++;
    }
    return array;
}

void csv_read(Traveloption **airplanes_array, Traveloption **trains_array, int *airplaneSize, int *trainSize)
{
    char line[1024];

    // opens airplanes file
    FILE *stream = fopen("airplanes.csv", "r");
    Traveloption airplaneOptions[18];

    // Read lines of airplanes file
    int i = 0;
    while (fgets(line, 1024, stream))
    {
        if (i != 0)
        {
            char *tmp = strdup(line);
            Traveloption item;
            char **option = splitString(tmp);

            item.startDest = option[0];
            item.endDest = option[1];
            sscanf(option[2], "%d", &item.travelTime);
            sscanf(option[3], "%lf", &item.price);
            sscanf(option[4], "%lf", &item.distance);

            // This is going to be used in the calcualte function
            item.score = 0;
            item.rank = 1;

            // Set type
            item.type = AIRPLANE;

            airplaneOptions[i - 1] = item;
            free(tmp);
        }
        i++;
    }
    fclose(stream);
    *airplaneSize = i - 1;
    *airplanes_array = malloc(sizeof(Traveloption) * (i - 1));
    // copy airplaneOptions data to airplanes_array memory adress
    memcpy(*airplanes_array, airplaneOptions, sizeof(Traveloption) * (i - 1));

    // opens trains file
    stream = fopen("trains.csv", "r");
    Traveloption trainOptions[18];
    // Read lines of trains file
    i = 0;
    while (fgets(line, 1024, stream))
    {
        if (i != 0)
        {
            char *tmp = strdup(line);
            Traveloption item;
            char **option = splitString(tmp);

            item.startDest = option[0];
            item.endDest = option[1];
            sscanf(option[2], "%d", &item.travelTime);
            sscanf(option[3], "%lf", &item.price);
            sscanf(option[4], "%lf", &item.distance);

            // This is going to be used in the calcualte function
            item.score = 0;
            item.rank = 1;

            // Set type
            item.type = TRAIN;

            trainOptions[i - 1] = item;

            free(tmp);
        }
        i++;
    }
    fclose(stream);

    *trainSize = i - 1;
    *trains_array = malloc(sizeof(Traveloption) * (i - 1));
    // copy trainOptions data to trains_array memory adress
    memcpy(*trains_array, trainOptions, sizeof(Traveloption) * (i - 1));
}