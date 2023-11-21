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

void csv_read(Traveloption **flights_array, Traveloption **trains_array, int *flightSize, int *trainSize)
{
    char line[1024];

    // opens flights file
    FILE *stream = fopen("flights.csv", "r");
    Traveloption flightOptions[18];

    // Read lines of flights file
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

            flightOptions[i - 1] = item;
            free(tmp);
        }
        i++;
    }
    fclose(stream);
    *flightSize = i - 1;
    *flights_array = malloc(sizeof(Traveloption) * (i - 1));
    // copy flightOptions data to flights_array memory adress
    memcpy(*flights_array, flightOptions, sizeof(Traveloption) * (i - 1));

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