#include <stdio.h>

void scan_user_input();

int passenger_amount();
int ratings(int);
void startpoint_and_destination();

void scan_user_input() // note: skal retunere rating, passenger antal og start-slut destination
{
    int number_of_passengers, co2_rating, price_rating, time_rating;

    number_of_passengers = passenger_amount();

    co2_rating = ratings(1);
    time_rating = ratings(2);
    price_rating = ratings(3);

    startpoint_and_destination();
}

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