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
    char from[20];
    char to[20];
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

// ---------------- FUNCTION DECLARATIONS ----------------
void registerUser();
int loginUser(char username[]);
void searchFlights(){}
void bookFlight(char username[]){}
int processPayment(int amount){}
void viewBookings(char username[]){}
void cancelBooking(char username[]){}



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
                    printf("\n----- MAIN MENU -----\n");
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
    if (strchr(password, ',') != NULL) {
        printf("Password cannot contain commas!\n");
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
            strcpy(username, user);
            fclose(fp);
            return 1; // user exists
        }
    }
    fclose(fp);
    printf("Invalid Username or Password!\n");
    return 0;
}