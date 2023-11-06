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

    do
    {
        printf("How many travelers are you planning to travel with? Between 1-100. (Including yourself): ");
        scanf(" %d", &amount);

        if (amount > 0 && amount >= 100)
        {
            printf("\nInvalid input:\n");
        }

    } while (amount > 0 && amount >= 100);

    return amount;
}

int ratings(int question)
{
    int answer;

    printf("\n");

    switch (question)
    {
    case 1:
        printf("On a scale of 1-5, indicate the extent to which you prioritize CO2 emmesions: ");
        break;

    case 2:
        printf("On a scale of 1-5, indicate the extent to which you prioritize travel time: ");
        break;

    case 3:
        printf("On a scale of 1-5, indicate the extent to which you prioritize the price: ");
        break;

    default:
        break;
    }

    scanf(" %d", &answer);

    while (answer <= 0 || answer > 5)
    {
        printf("\nInvalid input, must an integer between 1-5: ");
        scanf(" %d", &answer);
    }

    return answer;
}