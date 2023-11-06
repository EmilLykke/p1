#include <stdio.h>

void scan_user_input();
int passenger_amount();
void ratings();
void startpoint_and_destination();

int main(void)
{
    int number_of_passengers;

    number_of_passengers = passenger_amount();
}

int passenger_amount()
{
    int amount;
    int validInput;

    do
    {
        printf("How many travelers are you planning to travel with? Between 1-100. (Including yourself)\n");
        scanf(" %d", &amount);

        if (amount > 0 && amount >= 100)
        {
            printf("\nInvalid input:\n");
        }

    } while (amount > 0 && amount >= 100);

    return amount;
}