#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char *splitString(char *line, int num)
{
    const char *tok;
    for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n"))
    {
        if (!--num)
        {
            return tok;
        }
    }
    return NULL;
}

void csv_read()
{
    // opens flights file
    FILE *stream = fopen("flights.csv", "r");
    char line[1024];

    // Read lines of flights file
    while (fgets(line, 1024, stream))
    {
        char *tmp = strdup(line);

        printf("%s\n", splitString(tmp, 3));
        free(tmp);
    }
    fclose(stream);

    // opens trains file
    stream = fopen("trains.csv", "r");
    // Read lines of trains file
    while (fgets(line, 1024, stream))
    {
        char *tmp = strdup(line);

        printf("%s\n", splitString(tmp, 3));
        free(tmp);
    }
    fclose(stream);
}