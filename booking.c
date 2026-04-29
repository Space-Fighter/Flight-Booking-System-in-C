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
    struct Flight f;
    char confirm;

    for (int i = 0; i < flightCount; i++) {
        if (flights[i].flightNo == flightNo) {
            selectedIndex = i;
            break;
        }
    }

    if (selectedIndex == -1) {
        printf("Flight number not from filter menu. Returning to main.\n");
        free(flights);
        fclose(bp);
        return;
    }

    f = flights[selectedIndex];
    printf("Flight Selected:\n");
    display_flight(f);
    printf("Do you want to proceed with booking? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        int paymentSuccess = processPayment(f.price);
        if (!paymentSuccess) {
            printf("Payment failed! Booking cancelled.\n");
            free(flights);
            fclose(bp);
            return;
        }
        printf("Enter Passenger Name: ");
        readStr(passenger, sizeof(passenger));
        printf("USERNAME: %s\n", username);
        fprintf(bp, "%s,%s,%d,%d\n", username, passenger, f.flightNo, f.price);
        printf("Booking Confirmed! Amount Paid: Rs.%d\n", f.price);
    }
    else printf("Booking cancelled by user.\n");

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
    FILE *flightFp = fopen("flights.txt", "r");
    struct Flight f;

    if (fp == NULL) {
        printf("Unable to open bookings.txt!\n");
        return;
    }

    if (flightFp == NULL) {
        printf("Unable to open flights.txt!\n");
        fclose(fp);
        return;
    }

    printf("\nYour Bookings:\n");
    while (readBooking(fp, &b) == 4) {
        if (strcmp(b.username, username) == 0) {
            int found = 0;

            printf("Passenger: %s | Amount Paid: Rs.%d\n", b.passenger, b.amount);
            printf("Flight Details: ");

            rewind(flightFp);
            while (readFlightRecord(flightFp, &f)) {
                if (f.flightNo == b.flightNo) {
                    display_flight(f);
                    found = 1;
                    break;
                }
            }

            if (!found) {
                printf("Flight No: %d not found\n", b.flightNo);
            }
            printf("\n");
        }
    }
    fclose(fp);
    fclose(flightFp);
}

void cancelBooking(char username[]) {
    struct Booking b;
    struct Booking all[100];
    int count = 0;
    int userBookings[100];
    int userCount = 0;

    FILE *fp = fopen("bookings.txt", "r");

    printf("\nYour Bookings:\n");
    // Single loop: read + store + display together
    while (readBooking(fp, &b) == 4) {
        all[count] = b;                                  // store every record

        if (strcmp(b.username, username) == 0) {
            userBookings[userCount] = count;             // map user choice -> real index
            printf("%d. Passenger: %s | Flight No: %d | Amount Paid: Rs.%d\n",
                   ++userCount, b.passenger, b.flightNo, b.amount);
        }

        count++;
    }
    fclose(fp);

    if (userCount == 0) {
        printf("No bookings found.\n");
        return;
    }

    // Ask which to cancel
    int choice;
    printf("\nEnter booking number to cancel (0 to go back): ");
    scanf("%d", &choice);

    if (choice == 0) return;

    if (choice < 1 || choice > userCount) {
        printf("Invalid choice.\n");
        return;
    }

    int cancelIndex = userBookings[choice - 1];

    // Confirm
    printf("Are you sure you want to cancel booking for %s on Flight %d? (1=Yes / 0=No): ",
           all[cancelIndex].passenger, all[cancelIndex].flightNo);
    int confirm;
    scanf("%d", &confirm);
    if (confirm != 1) {
        printf("Cancellation aborted.\n");
        return;
    }

    // Rewrite file skipping cancelled record
    FILE *fw = fopen("bookings.txt", "w");
    if (fw == NULL) {
        printf("Error updating bookings!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (i == cancelIndex) continue;
        fprintf(fw, "%s,%s,%d,%d\n",
                all[i].username, all[i].passenger,
                all[i].flightNo, all[i].amount);
    }
    fclose(fw);

    printf("Booking cancelled successfully!\n");
}