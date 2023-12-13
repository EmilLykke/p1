// -----------------------------------------------------------------
//
//  File: scan_user_input.c
//
//  History: Dec-10-23
//
//------------------------------------------------------------------

#include "functions.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int ratings(int);
void startpoint_and_destination(char *, char *);

// Pass by reference to main with the user inputs
void scan_user_input(int *co2_rating, int *time_rating, int *price_rating, char *start, char *end)
{

    *co2_rating = ratings(1);
    *time_rating = ratings(2);
    *price_rating = ratings(3);

    startpoint_and_destination(start, end);
}

int ratings(int question)
{
    int answer;

    switch (question)
    {
    case 1:
        printf("\nOn a scale of 1-5, indicate the extent to which you prioritize reduction of CO2 emmesions: ");
        break;

    case 2:
        printf("\nOn a scale of 1-5, indicate the extent to which you prioritize fast travel time: ");
        break;

    case 3:
        printf("\nOn a scale of 1-5, indicate the extent to which you prioritize the price: ");
        break;

    default:
        break;
    }

    scanf(" %d", &answer);

    // Input error handling
    while (answer <= 0 || answer > 5)
    {
        printf("\nError: Must input an integer between 1-5: ");
        scanf(" %d", &answer);
    }

    return answer;
}

void startpoint_and_destination(char *start, char *end)
{
    printf("\nInput your starting destination: ");
    scanf("%s", start);

    printf("\nInput your end destination: ");
    scanf("%s", end);

    // Assigns the first letter of the string to be a capital letter
    start[0] = toupper(start[0]);
    end[0] = toupper(end[0]);
}
