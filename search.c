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

static int readFlightRecord(FILE *fp, struct Flight *f) {
    return fscanf(fp, "%d %s %s %d %d %d %d %d %d %d %d",
                  &f->flightNo, f->from, f->to,
                  &f->date.date, &f->date.month, &f->date.year,
                  &f->start_time.hour, &f->start_time.minute,
                  &f->end_time.hour, &f->end_time.minute,
                  &f->price) == 11;
}

void searchFlights() {
    char from[20], to[20];
    struct Date travelDate;
    struct Time travelTime;
    int minPrice, maxPrice;
    char useDate, useTime, usePrice;

    FILE *fp = fopen("flights.txt", "r");
    struct Flight f;

    if (!fp) {
        printf("Unable to open flights.txt!\n");
        return;
    }

    printf("\nEnter From: "); readStr(from, sizeof(from));
    printf("Enter To: "); readStr(to, sizeof(to));

    printf("Filter by Date? (y/n): ");
    scanf(" %c", &useDate); getchar();

    if (useDate == 'y' || useDate == 'Y') {
        printf("Enter Date: ");
        scanf("%d %d %d", &travelDate.date, &travelDate.month, &travelDate.year);
        getchar();
    }

    printf("\nAvailable Flights:\n");

    while (readFlightRecord(fp, &f)) {
        if (strcmp(f.from, from) == 0 && strcmp(f.to, to) == 0) {
            display_flight(f);
        }
    }

    fclose(fp);
}