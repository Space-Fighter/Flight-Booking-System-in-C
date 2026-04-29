#include "app.h"

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
                        case 1: {
                            struct Flight *flights = NULL;
                            searchFlights(&flights);
                            free(flights);
                            break;
                        }
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