#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// -------- STRUCTURES --------
struct Date {
    int date;
    int month;
    int year;
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

// -------- MACRO --------
#define readStr(buf, size) \
    fgets(buf, size, stdin); \
    buf[strcspn(buf, "\n")] = '\0';

// -------- FUNCTION DECLARATIONS --------
void display_date(struct Date d);
void display_time(struct Time t);
void display_flight(struct Flight f);

void registerUser();
int loginUser(char username[]);

int searchFlights(struct Flight **flights);
void bookFlight(char username[]);
int processPayment(int amount);

void viewBookings(char username[]);
void cancelBooking(char username[]);

#endif