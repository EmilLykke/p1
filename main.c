#include "functions.h"
#include <stdio.h>
#include <string.h>

enum train_or_plaine
{
    TRAIN = 1,
    AIRPLANE = 2,
};

void scan_user_input(int *, int *, int *, int *, char *, char *);
void csv_read();
void find_route(struct traveloption *airplane_or_train_option, char input_startdestination, char input_enddestination, int size, int *index1, int *index2, int *index3, int case);

int main(void)
{
    char startdestination[100];
    char enddestination[100];
    int co2_rating, time_rating, price_rating, number_of_passengers, size;
    int train_index1 = -1, train_index2 = -1, train_index3 = -1, airplane_index1 = -1, airplane_index2 = -1, airplane_index3 = -1;

    scan_user_input(&number_of_passengers, &co2_rating, &time_rating, &price_rating, &startdestination, &enddestination);

    csv_read();

    size = sizeof(array_train) / sizeof(array_train[0]);
    find_route(/* airplane_or_train_option*/, startdestination, enddestination, size, &train_index1, &train_index2, &train_index3, TRAIN);

    size = sizeof(array_airplane) / sizeof(array_airplane[0]);
    find_route(/* airplane_or_train_option*/, startdestination, enddestination, size, &airplane_index1, &airplane_index2, &airplane_index3, AIRPLANE);

    return 0;
}