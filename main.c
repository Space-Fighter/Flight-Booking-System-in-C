#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ---------------- STRUCTURES ----------------
struct Date {
    int date; // integer from 1 to 31
    int month; // integer from 1 to 12
    int year; // integer (e.g. 2024)
};

struct Time {
    int hour;
    int minute;
};

struct Flight {
    int flightNo;
    char from[50];
    char to[50];
    struct Date date;
    struct Time start_time;
    struct Time end_time;
    int price;
};

struct Booking {
    char username[100];
    char passenger[30];
    int flightNo;
    int amount;
};

// ---------------- HELPER MACRO ----------------

// Reads a string safely with fgets and strips the trailing newline
#define readStr(buf, size) \
    fgets(buf, size, stdin); \
    buf[strcspn(buf, "\n")] = '\0';

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

// ---------------- FUNCTION DECLARATIONS ----------------
void registerUser();
int loginUser(char username[]);
void searchFlights();
void bookFlight(char username[]);
int processPayment(int amount);
void viewBookings(char username[]);
void cancelBooking(char username[]);



// ------------------------- MAIN FUNCTION ---------------------
int main() {
    int choice;
    char username[100];
    while (1) {
        printf("\n==== GEU FLIGHT BOOKING SYSTEM ====\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // flush newline left by scanf

        if (choice == 1) {
            if (loginUser(username)) {
                printf("\nLogin Successful! Welcome %s\n", username);

                int option;
                while (1) {
                    printf("\n----- MAIN MENU -----\n%s\n", username);
                    printf("1. Search Flights\n");
                    printf("2. Book Flight\n");
                    printf("3. View My Bookings\n");
                    printf("4. Cancel Booking\n");
                    printf("5. Logout\n");
                    printf("Enter option: ");
                    scanf("%d", &option);
                    getchar(); // flush newline left by scanf

                    switch (option) {
                        case 1: searchFlights(); break;
                        case 2: bookFlight(username); break;
                        case 3: viewBookings(username); break;
                        case 4: cancelBooking(username); break;
                        case 5: goto logout;
                        default: printf("Invalid option!\n");
                    }
                }
            }
        }
        else if (choice == 2) {
            registerUser();
        }
        else if (choice == 3) {
            printf("Exiting...");
            return 0;
        }
        else {
            printf("Invalid Choice!\n");
        }

        logout:
            continue;
    }
}

// Register a new user
int CheckUserExist(char username[], FILE *fp) {
    if (strchr(username, ' ') != NULL) {
        printf("Username cannot contain spaces!\n");
        return 1; // treat as existing to prevent registration
    }
    char LINE[200], file_user[100], file_pass[100];
    while (fscanf(fp, "%s %s", file_user, file_pass) != EOF) {
        if (strcmp(file_user, username) == 0) {
            printf("Username already exists! Please choose a different username.\n");
            return 1; // user exists
        }
    }
    return 0; // user does not exist
}

int CheckValidPassword(char password[]) {
    if (strlen(password) < 6) {
        printf("Password must be at least 6 characters long!\n");
        return 0;
    }
    if (strchr(password, ' ') != NULL) {
        printf("Password cannot contain spaces!\n");
        return 0;
    }
    if (strchr(password, ',') != NULL) {
        printf("Password cannot contain commas!\n");
        return 0;
    }
    return 1;
}

void registerUser() {
    FILE *fp = fopen("users.txt", "a+");
    char username[100], password[100];
    printf("\nEnter Username: ");
    readStr(username, sizeof(username));
    if (CheckUserExist(username, fp)) {
        fclose(fp);
        return;
    }
    printf("Enter Password: ");
    readStr(password, sizeof(password));

    if (!CheckValidPassword(password)) {
        fclose(fp);
        return;
    }
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);
    printf("Registration Successful! You can now login.\n");
}

// LOGIN
int loginUser(char username[]){
    char user[100], pass[100];
    FILE *fp = fopen("users.txt", "r");
    printf("\nEnter Username: ");
    readStr(user, sizeof(user));
    printf("Enter Password: ");
    readStr(pass, sizeof(pass));

    char file_user[100], file_pass[100];
    while (fscanf(fp, "%s %s", file_user, file_pass) != EOF) {
        if (strcmp(file_user, user) == 0 && strcmp(file_pass, pass) == 0) {
            fclose(fp);
            strcpy(username, user);
            return 1; // user exists
        }
    }
    fclose(fp);
    printf("Invalid Username or Password!\n");
    return 0;
}

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

// SEARCH FLIGHTS
void searchFlights() {
    char from[20], to[20];
    struct Date travelDate;
    struct Time travelTime;
    int minPrice, maxPrice;
    char useDate, useTime, usePrice;
    FILE *fp = fopen("flights.txt", "r");
    struct Flight f;

    if (fp == NULL) {
        printf("Unable to open flights.txt!\n");
        return;
    }

    printf("\nEnter From: ");
    readStr(from, sizeof(from));

    printf("Enter To: ");
    readStr(to, sizeof(to));

    printf("Filter by Date? (y/n): ");
    scanf(" %c", &useDate);
    getchar(); // flush newline left by scanf
    if (useDate == 'y' || useDate == 'Y') {
        printf("Enter Date (DD MM YYYY): ");
        scanf("%d %d %d", &travelDate.date, &travelDate.month, &travelDate.year);
        getchar(); // flush newline left by scanf
    }

    printf("Filter by Start Time? (y/n): ");
    scanf(" %c", &useTime);
    getchar(); // flush newline left by scanf
    if (useTime == 'y' || useTime == 'Y') {
        printf("Enter Time (HH MM): ");
        scanf("%d %d", &travelTime.hour, &travelTime.minute);
        getchar(); // flush newline left by scanf
    }

    printf("Filter by Price Range? (y/n): ");
    scanf(" %c", &usePrice);
    getchar(); // flush newline left by scanf
    if (usePrice == 'y' || usePrice == 'Y') {
        printf("Enter Price Range (min max): ");
        scanf("%d %d", &minPrice, &maxPrice);
        getchar(); // flush newline left by scanf
    }

    printf("\nAvailable Flights:\n");
    int found = 0;

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
            found = 1;
            display_flight(f);
        }
    }

    if (!found)
        printf("No flights found!\n");

    fclose(fp);
}

// BOOK FLIGHT
void bookFlight(char username[]) {
    char passenger[30];
    FILE *fp = fopen("flights.txt", "r");
    FILE *bp = fopen("bookings.txt", "a");
    printf("Let us know where is your dream destination:\n");
    searchFlights();

    printf("\nEnter Flight Number to Book: ");
    int flightNo;
    scanf("%d", &flightNo);
    struct Flight f;
    char confirm;
    while (readFlightRecord(fp, &f)){
        if (flightNo == f.flightNo) {
            printf("Flight Selected:\n");
            display_flight(f);
            printf("Do you want to proceed with booking? (y/n): ");
            scanf(" %c", &confirm);
            break;
        }
    }

    if (confirm == 'y' || confirm == 'Y') {
        int paymentSuccess = processPayment(f.price);
        if (!paymentSuccess) {
            printf("Payment failed! Booking cancelled.\n");
            fclose(fp);
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
    fclose(fp);
    fclose(bp);
}

int processPayment(int amount) {
    int method;

    printf("\n===== PAYMENT GATEWAY =====\n");
    printf("Amount to Pay: Rs.%d\n", amount);
    printf("Select Payment Method:\n");
    printf("1. Credit/Debit Card\n");
    printf("2. UPI\n");
    printf("3. Net Banking\n");
    printf("Enter choice: ");
    scanf("%d", &method);
    getchar(); // flush newline left by scanf

    if (method == 1) {
        char cardNo[20], cvv[5], expiry[8];

        printf("\n-- Card Payment --\n");
        printf("Enter Card Number (16 digits): ");
        readStr(cardNo, sizeof(cardNo));

        if (strlen(cardNo) != 16) {
            printf("Invalid card number!\n");
            return 0;
        }

        printf("Enter CVV (3 digits): ");
        readStr(cvv, sizeof(cvv));

        if (strlen(cvv) != 3) {
            printf("Invalid CVV!\n");
            return 0;
        }

        printf("Enter Expiry Date (MM/YY): ");
        readStr(expiry, sizeof(expiry));

        printf("\nProcessing payment...\n");
        printf("Payment of Rs.%d successful via Card!\n", amount);
        return 1;
    }
    else if (method == 2) {
        char upiId[30];

        printf("\n-- UPI Payment --\n");
        printf("Enter UPI ID (e.g. name@upi): ");
        readStr(upiId, sizeof(upiId));

        if (strchr(upiId, '@') == NULL) {
            printf("Invalid UPI ID!\n");
            return 0;
        }

        printf("\nProcessing payment...\n");
        printf("Payment of Rs.%d successful via UPI!\n", amount);
        return 1;
    }
    else if (method == 3) {
        char bank[20], accNo[20];

        printf("\n-- Net Banking --\n");
        printf("Enter Bank Name: ");
        readStr(bank, sizeof(bank));

        printf("Enter Account Number: ");
        readStr(accNo, sizeof(accNo));

        if (strlen(accNo) < 8) {
            printf("Invalid account number!\n");
            return 0;
        }

        printf("\nProcessing payment...\n");
        printf("Payment of Rs.%d successful via Net Banking!\n", amount);
        return 1;
    }
    else {
        printf("Invalid payment method!\n");
        return 0;
    }
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