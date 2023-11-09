#include <stdio.h>
#include <string.h>
#include <stdio.h>

void scan_user_input(int *number_of_passengers, int *co2_rating, int *time_rating, int *price_rating, char *start, char *end);

int main(void)
{
    char startdestination[100];
    char enddestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers;

    scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, startdestination, enddestination);

    return 0;
}