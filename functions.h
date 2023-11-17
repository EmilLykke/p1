enum train_or_plaine
{
    TRAIN = 1,
    AIRPLANE = 2,
};

typedef struct
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

// Finds route and calculates remaining factors
void find_route(Traveloption *, char, char, int, int *, int *, int *, int);

// CSV file reader
void csv_read(Traveloption **, Traveloption **);
