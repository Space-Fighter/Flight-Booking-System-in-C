#include "app.h"

void bookFlight(char username[]) {
    char passenger[30];
    FILE *bp = fopen("bookings.txt", "a");

    struct Flight *flights = NULL;
    int flightCount;

    if (bp == NULL) {
        printf("Unable to open bookings.txt!\n");
        return;
    }

    printf("Let us know where is your dream destination:\n");

    flightCount = searchFlights(&flights);

    if (flightCount == 0) {
        printf("Returning to main menu.\n");
        fclose(bp);
        free(flights);
        return;
    }

    printf("\nEnter Flight Number to Book: ");
    int flightNo;
    scanf("%d", &flightNo);

    int selectedIndex = -1;

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightNo == flightNo) {
            selectedIndex = i;
            break;
        }
    }

    if (selectedIndex == -1) {
        printf("Invalid flight number.\n");
        free(flights);
        fclose(bp);
        return;
    }

    struct Flight f = flights[selectedIndex];

    printf("Flight Selected:\n");
    display_flight(f);

    char confirm;
    printf("Do you want to proceed with booking? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        if (!processPayment(f.price)) {
            printf("Payment failed!\n");
            free(flights);
            fclose(bp);
            return;
        }

        printf("Enter Passenger Name: ");
        getchar();
        readStr(passenger, sizeof(passenger));

        fprintf(bp, "%s,%s,%d,%d\n", username, passenger, f.flightNo, f.price);
        printf("Booking Confirmed!\n");
    }

    free(flights);
    fclose(bp);
}

// VIEW BOOKINGS
static int readBooking(FILE *fp, struct Booking *b) {
    return fscanf(fp, " %[^,],%[^,],%d,%d",
                  b->username,
                  b->passenger,
                  &b->flightNo,
                  &b->amount);
}

void viewBookings(char username[]) {
    struct Booking b;
    FILE *fp = fopen("bookings.txt", "r");

    if (fp == NULL) {
        printf("Unable to open bookings.txt!\n");
        return;
    }

    printf("\nYour Bookings:\n");

    while (readBooking(fp, &b) == 4) {
        if (strcmp(b.username, username) == 0) {
            printf("Passenger: %s | Flight No: %d | Amount Paid: Rs.%d\n",
                   b.passenger, b.flightNo, b.amount);
        }
    }

    fclose(fp);
}

void cancelBooking(char username[]) {
    struct Booking b;
    struct Booking all[100];
    int count = 0;

    FILE *fp = fopen("bookings.txt", "r");

    if (!fp) {
        printf("Unable to open bookings.txt!\n");
        return;
    }

    while (readBooking(fp, &b) == 4) {
        all[count++] = b;
    }
    fclose(fp);

    FILE *fw = fopen("bookings.txt", "w");

    for (int i = 0; i < count; i++) {
        if (strcmp(all[i].username, username) != 0) {
            fprintf(fw, "%s,%s,%d,%d\n",
                    all[i].username,
                    all[i].passenger,
                    all[i].flightNo,
                    all[i].amount);
        }
    }

    fclose(fw);
    printf("All your bookings cancelled.\n");
}