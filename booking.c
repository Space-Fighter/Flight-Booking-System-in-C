#include "app.h"

static int readBooking(FILE *fp, struct Booking *b) {
    return fscanf(fp, " %[^,],%[^,],%d,%d",
                  b->username, b->passenger,
                  &b->flightNo, &b->amount);
}

void bookFlight(char username[]) {
    char passenger[30];
    FILE *fp = fopen("flights.txt", "r");
    FILE *bp = fopen("bookings.txt", "a");

    searchFlights();

    printf("\nEnter Flight Number: ");
    int flightNo;
    scanf("%d", &flightNo);

    struct Flight f;
    char confirm;

    while (fscanf(fp, "%d", &f.flightNo) != EOF) {
        if (flightNo == f.flightNo) {
            printf("Confirm booking? (y/n): ");
            scanf(" %c", &confirm);
            break;
        }
    }

    if (confirm == 'y' || confirm == 'Y') {
        int paymentSuccess = processPayment(f.price);

        if (!paymentSuccess) return;

        printf("Enter Passenger Name: ");
        readStr(passenger, sizeof(passenger));

        fprintf(bp, "%s,%s,%d,%d\n", username, passenger, f.flightNo, f.price);
        printf("Booking Confirmed!\n");
    }

    fclose(fp);
    fclose(bp);
}

void viewBookings(char username[]) {
    struct Booking b;
    FILE *fp = fopen("bookings.txt", "r");

    while (readBooking(fp, &b) == 4) {
        if (strcmp(b.username, username) == 0) {
            printf("%s | Flight %d | Rs.%d\n", b.passenger, b.flightNo, b.amount);
        }
    }
    fclose(fp);
}

void cancelBooking(char username[]) {
    printf("Cancel feature working...\n");
}