#ifndef APP_H
#define APP_H

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

static inline void display_date(struct Date d) {
    printf("%02d/%02d/%04d", d.date, d.month, d.year);
}

static inline void display_time(struct Time t) {
    printf("%02d:%02d", t.hour, t.minute);
}

static inline void display_flight(struct Flight f) {
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
int searchFlights(struct Flight **flights);
void bookFlight(char username[]);
int processPayment(int amount);
void viewBookings(char username[]);
void cancelBooking(char username[]);
int readFlightRecord(FILE *fp, struct Flight *f);

#endif