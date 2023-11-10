#include <stdio.h>
#include <string.h>

void find_route(struct traveloption *, char *, char *, int);

/* struct traveloption
{
    char startdest[100];
    char enddest[100];
    int traveltime;
    int price;
    int co2;
}; */

// i en funktionen den kaldes i skal man benytte sizeof til at finde str af de to arrays når de sendes til funktionen her.
// den vil retunere indexet af den string der har det samme navn i data sættet i startdest og slutdest

int find_route(struct traveloption *airplane_or_train_option, char *input_startdestination, char *input_enddestination, int size)
{
    int i;
    // int size = sizeof(airplane_or_train_option) / sizeof(airplane_or_train_option[0]); // calculates size of  array

    for (i = 0; i < size; i++)
    {
        if (strcmp(airplane_or_train_option[i].startdest, input_startdestination) && strcmp(airplane_or_train_option[i].enddest, input_enddestination))
        {
            return i; // returns the index of the correct array travel option
        }
    }

    return -1; // couldn't find the designated travel option in the dataset
}
