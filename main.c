#include <stdio.h>
#include <string.h>

void scan_user_input(int *, int *, int *, int *, char *, char *);

int main(void)
{
    char startdestination[100];
    char enddestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers;

    scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, startdestination, enddestination);

    return 0;
}