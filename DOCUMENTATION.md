# GEU Flight Booking System Documentation

## Project Summary
This is a console-based flight booking system written in C. It uses text files to store users, flights, and bookings, and it provides a simple menu-driven interface for registration, login, flight search, booking, booking display, and cancellation.

The current implementation is contained in `my_code.c` and follows this flow:
1. User logs in or registers.
2. After login, the main menu appears.
3. The user can search flights, book a flight, view bookings, cancel a booking, or log out.

## Structures Used

### `struct Date`
```c
struct Date {
    int date;
    int month;
    int year;
};
```
Purpose: stores a calendar date in `DD MM YYYY` form.

Related concept: a structure groups multiple data fields into one named type. Here, a date is represented by three integers instead of one string.

### `struct Time`
```c
struct Time {
    int hour;
    int minute;
};
```
Purpose: stores time in `HH:MM` form.

### `struct Flight`
```c
struct Flight {
    int flightNo;
    char from[50];
    char to[50];
    struct Date date;
    struct Time start_time;
    struct Time end_time;
    int price;
};
```
Purpose: stores one flight record.

Fields:
- `flightNo`: unique flight number
- `from`: departure city
- `to`: destination city
- `date`: travel date
- `start_time`: departure time
- `end_time`: arrival time
- `price`: ticket price

### `struct Booking`
```c
struct Booking {
    char username[100];
    char passenger[30];
    int flightNo;
    int amount;
};
```
Purpose: stores one booking record.

Fields:
- `username`: the logged-in account that created the booking
- `passenger`: passenger name entered during booking
- `flightNo`: booked flight number
- `amount`: paid amount

## Function Documentation

### `main()`
```c
int main() {
```
Purpose: controls the entire program flow.

How it works:
- Shows the login/register menu.
- Calls `loginUser()` or `registerUser()` based on the user's choice.
- After successful login, shows the main menu.
- Dispatches to `searchFlights()`, `bookFlight()`, `viewBookings()`, and `cancelBooking()`.

Related C concepts:
- `while (1)` creates an infinite loop.
- `switch` selects one of several actions based on the user's menu choice.
- `goto logout;` is used to jump out of the inner menu loop when the user logs out.

---

### `registerUser()`
```c
void registerUser() {
```
Purpose: registers a new user and appends the credentials to `users.txt`.

How it works:
- Opens `users.txt` in append mode with `fopen()`.
- Reads username and password using the `readStr` macro, which internally uses `fgets()`.
- Calls `CheckUserExist()` to prevent duplicate usernames.
- Writes the new record using `fprintf()`.

Library functions used:
- `fopen("users.txt", "a+")`: opens the file for reading and appending.
- `fprintf(fp, "%s %s\n", username, password)`: writes formatted text to a file.
- `fclose(fp)`: closes the file after writing.
- `strchr(password, ',')`: checks whether the password contains a comma.

Example:
```c
FILE *fp = fopen("users.txt", "a+");
fprintf(fp, "%s %s\n", username, password);
fclose(fp);
```

Related concept:
- File append mode adds new data without deleting existing records.

---

### `CheckUserExist(char username[], FILE *fp)`
```c
int CheckUserExist(char username[], FILE *fp) {
```
Purpose: checks whether a username already exists in `users.txt`.

How it works:
- Scans each record in the user file with `fscanf()`.
- Compares the stored username with the input using `strcmp()`.
- Returns `1` if the username exists, otherwise `0`.

Library functions used:
- `fscanf(fp, "%s %s", file_user, file_pass)`: reads whitespace-separated strings from a file.
- `strcmp(a, b)`: compares two strings.
- `strchr(username, ' ')`: checks whether the username contains a space.

Example:
```c
while (fscanf(fp, "%s %s", file_user, file_pass) != EOF) {
    if (strcmp(file_user, username) == 0) {
        return 1;
    }
}
```

Related concept:
- `strcmp()` returns `0` when strings are equal.

---

### `CheckValidPassword(char password[])`
```c
int CheckValidPassword(char password[]) {
```
Purpose: validates password rules.

How it works:
- Ensures the password length is at least 6 characters using `strlen()`.
- Rejects passwords containing spaces.

Library functions used:
- `strlen(password)`: returns the length of the string.
- `strchr(password, ' ')`: checks for a space character.

Related concept:
- String validation is a basic input sanitization step.

---

### `loginUser(char username[])`
```c
int loginUser(char username[]) {
```
Purpose: verifies the user's login credentials.

How it works:
- Reads the username and password from the keyboard.
- Opens `users.txt` in read mode.
- Reads each stored user record using `fscanf()`.
- Compares the entered values with the stored values using `strcmp()`.
- If a match is found, copies the username into the output parameter and returns success.

Library functions used:
- `fopen("users.txt", "r")`: opens a file for reading.
- `fscanf(fp, "%s %s", file_user, file_pass)`: reads two space-separated fields.
- `strcmp(file_user, user)`: compares usernames.
- `strcmp(file_pass, pass)`: compares passwords.
- `strcpy(username, user)`: copies the logged-in username to the caller.

Example:
```c
FILE *fp = fopen("users.txt", "r");
while (fscanf(fp, "%s %s", file_user, file_pass) != EOF) {
    if (strcmp(file_user, user) == 0 && strcmp(file_pass, pass) == 0) {
        strcpy(username, user);
        fclose(fp);
        return 1;
    }
}
```

Related concept:
- Output parameters like `char username[]` let a function return more than one value indirectly.

---

### `readFlightRecord(FILE *fp, struct Flight *f)`
```c
static int readFlightRecord(FILE *fp, struct Flight *f) {
```
Purpose: reads one flight record from `flights.txt` into a `struct Flight`.

How it works:
- Uses `fscanf()` to parse one line.
- Stores the data directly into the structure fields.
- Returns `1` when a full record is read successfully, otherwise `0`.

Library functions used:
- `fscanf()` with a format string matching the file layout.

Example:
```c
fscanf(fp, "%d %s %s %d %d %d %d %d %d %d %d", ...);
```

Related concept:
- This helper function centralizes flight-file parsing so search and booking use the same logic.

---

### `searchFlights()`
```c
void searchFlights() {
```
Purpose: searches and displays flights from `flights.txt`.

How it works:
- Reads source and destination cities.
- Optionally reads date, time, and price filters.
- Iterates through all flight records using `readFlightRecord()`.
- Prints only matching flights.

Library functions used:
- `fopen("flights.txt", "r")`: opens the flight data file.
- `strcmp()`: compares city names.
- `scanf()`: reads menu-driven filter input.
- `getchar()`: clears the newline left behind by `scanf()`.
- `printf()`: displays results.

Example:
```c
if (strcmp(f.from, from) == 0 && strcmp(f.to, to) == 0) {
    display_flight(f);
}
```

Related concept:
- Logical operators are used to combine optional filters.

---

### `bookFlight(char username[])`
```c
void bookFlight(char username[]) {
```
Purpose: books a selected flight and stores the booking.

How it works:
- Calls `searchFlights()` so the user can see available flights.
- Reads a flight number from the keyboard.
- Scans `flights.txt` until it finds a matching flight number.
- Asks for confirmation.
- Calls `processPayment()` to simulate payment.
- Reads the passenger name.
- Appends a booking record to `bookings.txt`.

Library functions used:
- `fopen("flights.txt", "r")`: opens flight data for lookup.
- `fopen("bookings.txt", "a")`: opens bookings file in append mode.
- `scanf("%d", &flightNo)`: reads the selected flight number.
- `fprintf(bp, "%s,%s,%d,%d\n", ...)`: writes one booking record.

Example:
```c
fprintf(bp, "%s,%s,%d,%d\n", username, passenger, f.flightNo, f.price);
```

Related concept:
- Appending to a booking file preserves all earlier bookings.

---

### `processPayment(int amount)`
```c
int processPayment(int amount) {
```
Purpose: simulates a payment gateway.

How it works:
- Prints the amount to pay.
- Lets the user choose a payment method.
- Validates the chosen method's required details.
- Returns `1` for success and `0` for failure.

Library functions used:
- `printf()`: displays payment prompts.
- `scanf()`: reads the payment method.
- `readStr()`: reads card number, CVV, UPI ID, or account number.
- `strlen()`: validates input length.
- `strchr()`: checks for `@` in a UPI ID.

Related concept:
- This function is a mock payment flow, not a real payment integration.

---

### `readBooking(FILE *fp, struct Booking *b)`
```c
static int readBooking(FILE *fp, struct Booking *b) {
```
Purpose: reads one comma-separated booking record from `bookings.txt`.

How it works:
- Uses `fscanf()` with a CSV-style format string.
- Stores the username, passenger, flight number, and amount into the booking structure.

Library functions used:
- `fscanf(fp, " %[^,],%[^,],%d,%d", ...)`: reads text up to commas.

Related concept:
- `%[^,]` means “read characters until a comma is found.”

Example:
```c
fscanf(fp, " %[^,],%[^,],%d,%d", b->username, b->passenger, &b->flightNo, &b->amount);
```

---

### `viewBookings(char username[])`
```c
void viewBookings(char username[]) {
```
Purpose: shows bookings that belong only to the logged-in user.

How it works:
- Opens `bookings.txt`.
- Reads every booking using `readBooking()`.
- Compares `b.username` with the logged-in username using `strcmp()`.
- Prints matching records only.

Library functions used:
- `fopen("bookings.txt", "r")`: opens the bookings file for reading.
- `strcmp()`: filters records by username.
- `printf()`: displays booking information.

Related concept:
- Filtering by username gives each user a private booking view.

---

### `cancelBooking(char username[])`
```c
void cancelBooking(char username[]) {
```
Purpose: cancels one of the current user's bookings.

How it works:
- Reads all bookings into memory.
- Collects only the current user's bookings for display.
- Lets the user select which booking to cancel.
- Confirms the choice.
- Rewrites `bookings.txt` without the selected entry.

Library functions used:
- `fopen("bookings.txt", "r")`: reads existing bookings.
- `fopen("bookings.txt", "w")`: rewrites the file after cancellation.
- `scanf()`: reads the cancellation choice and confirmation.
- `fprintf()`: writes the remaining bookings back to the file.
- `strcmp()`: matches bookings to the logged-in user.

Related concept:
- Opening a file in write mode truncates the old file, so only remaining records are saved.

---

### `display_date(struct Date d)`
```c
void display_date(struct Date d) {
```
Purpose: prints a date in `DD/MM/YYYY` format.

Library functions used:
- `printf("%02d/%02d/%04d", ...)`: formats numbers with leading zeros.

### `display_time(struct Time t)`
```c
void display_time(struct Time t) {
```
Purpose: prints a time in `HH:MM` format.

Library functions used:
- `printf("%02d:%02d", ...)`: formats time values cleanly.

### `display_flight(struct Flight f)`
```c
void display_flight(struct Flight f) {
```
Purpose: prints a flight record in a readable single-line format.

How it works:
- Prints flight number, source, destination, date, time, and price.
- Uses `display_date()` and `display_time()` internally.

## C Library Functions Used

### `fopen()`
Syntax:
```c
FILE *fopen(const char *filename, const char *mode);
```
Usage in this project:
- `fopen("users.txt", "r")` reads users.
- `fopen("users.txt", "a+")` appends new users.
- `fopen("flights.txt", "r")` reads flight data.
- `fopen("bookings.txt", "a")` appends bookings.

Example:
```c
FILE *fp = fopen("users.txt", "r");
```

### `fclose()`
Syntax:
```c
int fclose(FILE *stream);
```
Usage:
- Closes a file after reading or writing.

Example:
```c
fclose(fp);
```

### `fscanf()`
Syntax:
```c
int fscanf(FILE *stream, const char *format, ...);
```
Usage:
- Reads formatted data from a file.
- Used for `users.txt`, `flights.txt`, and `bookings.txt`.

Example:
```c
fscanf(fp, "%d %s %s %d %d %d %d %d %d %d %d", ...);
```

### `fprintf()`
Syntax:
```c
int fprintf(FILE *stream, const char *format, ...);
```
Usage:
- Writes formatted data to files.

Example:
```c
fprintf(bp, "%s,%s,%d,%d\n", username, passenger, f.flightNo, f.price);
```

### `printf()`
Syntax:
```c
int printf(const char *format, ...);
```
Usage:
- Displays prompts, menus, results, and confirmations on screen.

### `scanf()`
Syntax:
```c
int scanf(const char *format, ...);
```
Usage:
- Reads numeric and character input from the keyboard.

### `fgets()`
Syntax:
```c
char *fgets(char *str, int n, FILE *stream);
```
Usage:
- Safely reads full strings including spaces.
- Used inside the `readStr` macro.

### `strcmp()`
Syntax:
```c
int strcmp(const char *s1, const char *s2);
```
Usage:
- Compares two strings.
- Returns `0` when both strings are equal.

### `strcpy()`
Syntax:
```c
char *strcpy(char *dest, const char *src);
```
Usage:
- Copies the logged-in username into the caller's buffer.

### `strlen()`
Syntax:
```c
size_t strlen(const char *s);
```
Usage:
- Checks string length during password and payment validation.

### `strchr()`
Syntax:
```c
char *strchr(const char *s, int c);
```
Usage:
- Searches for a character inside a string.
- Used for spaces, commas, and `@` checks.

### `strcspn()`
Syntax:
```c
size_t strcspn(const char *s1, const char *s2);
```
Usage:
- Removes the newline added by `fgets()` in the `readStr` macro.

## File Formats

### `users.txt`
```text
username password
```

### `flights.txt`
```text
flightNo from to date month year startHour startMinute endHour endMinute price
```

### `bookings.txt`
```text
username,passenger,flightNo,amount
```

## Important Notes
- The code depends on fixed file formats.
- `viewBookings()` and `cancelBooking()` work only if `bookings.txt` is comma-separated.
- `searchFlights()` and `bookFlight()` work only if `flights.txt` is space-separated in the expected order.
- `readStr` is a macro, not a normal function; it wraps `fgets()` plus newline trimming.

## Summary
The project demonstrates core C programming concepts:
- structures
- file handling
- string processing
- menu-driven logic
- record-based data storage

It is a good example of building a small persistent application without using a database.
