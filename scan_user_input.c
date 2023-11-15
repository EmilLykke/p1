#include "functions.h"
#include <stdio.h>
#include <string.h>

int passenger_amount()
{
    int amount;

    printf("How many travelers are you planning to travel with? Between 1-100. (Including yourself): ");
    scanf(" %d", &amount);

    while (amount < 0 || amount > 100)
    {
        printf("\nError: Must input between 1-100, try again: ");
        scanf("%d", &amount);
    }
    return amount;
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

    while (answer <= 0 || answer > 5)
    {
        printf("\nError: Must input an integer between 1-5: ");
        scanf(" %d", &answer);
    }

    return answer;
}

void startpoint_and_destination(char *start, char *end)
{
    printf("Input your starting destination: ");
    scanf("%s", start);

    printf("\nInput your end destination: ");
    scanf("%s", end);

    toupper(start[0]);
    toupper(end[0]);
}

void scan_user_input(int *number_of_passengers, int *co2_rating, int *time_rating, int *price_rating, char *start, char *end)
{

    *number_of_passengers = passenger_amount();

    *co2_rating = ratings(1);
    *time_rating = ratings(2);
    *price_rating = ratings(3);

    startpoint_and_destination(start, end);
}