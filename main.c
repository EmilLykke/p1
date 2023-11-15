#include "functions.h"
#include <stdio.h>
#include <string.h>

void scan_user_input(int *, int *, int *, int *, char *, char *);
void csv_read();
void find_route(Traveloption *, char, char, int, int *, int *, int *, int);

int main(void)
{
    char startDestination[100];
    char endDestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers, size;
    int train_index1 = -1, train_index2 = -1, train_index3 = -1, airplane_index1 = -1, airplane_index2 = -1, airplane_index3 = -1;

    scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, &startDestination, &endDestination);

    csv_read();

    size = sizeof(array_train) / sizeof(array_train[0]);
    find_route(/* airplane_or_train_option*/, startDestination, endDestination, size, &train_index1, &train_index2, &train_index3, TRAIN);

    size = sizeof(array_airplane) / sizeof(array_airplane[0]);
    find_route(/* airplane_or_train_option*/, startDestination, endDestination, size, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

    return 0;
}