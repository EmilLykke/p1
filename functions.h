enum train_or_plaine
{
    TRAIN = 1,
    AIRPLANE = 2,
};

// Scans user input
void scan_user_input(int *, int *, int *, int *, char *, char *);

// Read csv files
void csv_read();

// Finds route and calculates remaining factors
void find_route(Traveloption *, char, char, int, int *, int *, int *, int);