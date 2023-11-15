
typedef struct Traveloption
{
    char *startDest;
    char *endDest;
    int travelTime;
    double price;
    int co2;
    double distance;
    int wasteTime;
    int totalTime;
} Traveloption;

// Scans user input
void scan_user_input(int *, int *, int *, int *, char *, char *);

// Read csv files
void csv_read();
