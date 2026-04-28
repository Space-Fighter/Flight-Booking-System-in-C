#include "app.h"

void display_date(struct Date d) {
    printf("%02d/%02d/%04d", d.date, d.month, d.year);
}

void display_time(struct Time t) {
    printf("%02d:%02d", t.hour, t.minute);
}

void display_flight(struct Flight f) {
    printf("%d | %s -> %s | ", f.flightNo, f.from, f.to);
    display_date(f.date);
    printf(" | ");
    display_time(f.start_time);
    printf(" - ");
    display_time(f.end_time);
    printf(" | Rs.%d\n", f.price);
}

// Needed for reading file
static int readFlightRecord(FILE *fp, struct Flight *f) {
    return fscanf(fp, "%d %s %s %d %d %d %d %d %d %d %d",
                  &f->flightNo,
                  f->from,
                  f->to,
                  &f->date.date,
                  &f->date.month,
                  &f->date.year,
                  &f->start_time.hour,
                  &f->start_time.minute,
                  &f->end_time.hour,
                  &f->end_time.minute,
                  &f->price) == 11;
}

// SEARCH FLIGHTS (DMA VERSION)
int searchFlights(struct Flight **flights){
    char from[20], to[20];
    struct Date travelDate;
    struct Time travelTime;
    int minPrice, maxPrice;
    char useDate, useTime, usePrice;
    FILE *fp = fopen("flights.txt", "r");
    struct Flight f;
    int found = 0;
    int capacity = 0;

    if (fp == NULL) {
        printf("Unable to open flights.txt!\n");
        return 0;
    }

    *flights = NULL;

    printf("\nEnter From: ");
    readStr(from, sizeof(from));

    printf("Enter To: ");
    readStr(to, sizeof(to));

    printf("Filter by Date? (y/n): ");
    scanf(" %c", &useDate); getchar();
    if (useDate == 'y' || useDate == 'Y') {
        printf("Enter Date (DD MM YYYY): ");
        scanf("%d %d %d", &travelDate.date, &travelDate.month, &travelDate.year);
        getchar();
    }

    printf("Filter by Start Time? (y/n): ");
    scanf(" %c", &useTime); getchar();
    if (useTime == 'y' || useTime == 'Y') {
        printf("Enter Time (HH MM): ");
        scanf("%d %d", &travelTime.hour, &travelTime.minute);
        getchar();
    }

    printf("Filter by Price Range? (y/n): ");
    scanf(" %c", &usePrice); getchar();
    if (usePrice == 'y' || usePrice == 'Y') {
        printf("Enter Price Range (min max): ");
        scanf("%d %d", &minPrice, &maxPrice);
        getchar();
    }

    printf("\nAvailable Flights:\n");

    while (readFlightRecord(fp, &f)) {

        if (strcmp(f.from, from) == 0 &&
            strcmp(f.to, to) == 0 &&
            (useDate != 'y' && useDate != 'Y' ||
             (f.date.date == travelDate.date &&
              f.date.month == travelDate.month &&
              f.date.year == travelDate.year)) &&
            (useTime != 'y' && useTime != 'Y' ||
             (f.start_time.hour == travelTime.hour &&
              f.start_time.minute == travelTime.minute)) &&
            (usePrice != 'y' && usePrice != 'Y' ||
             (f.price >= minPrice && f.price <= maxPrice))) {

            if (found == capacity) {
                int newCapacity = (capacity == 0) ? 10 : capacity * 2;
                struct Flight *temp = realloc(*flights, newCapacity * sizeof(struct Flight));

                if (temp == NULL) {
                    printf("Memory allocation failed!\n");
                    free(*flights);
                    *flights = NULL;
                    fclose(fp);
                    return 0;
                }

                *flights = temp;
                capacity = newCapacity;
            }

            (*flights)[found++] = f;
            display_flight(f);
        }
    }

    if (!found)
        printf("No flights found!\n");

    fclose(fp);
    return found;
}