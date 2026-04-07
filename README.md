# GEU Flight Booking System

## Overview
This project is a console-based flight booking application written in C. It lets a user register, log in, search for flights, book a flight, view their bookings, and cancel a booking.

The program is menu-driven and uses plain text files to persist data between runs.

## What the code does
- Starts with a login/register screen.
- Verifies credentials from `users.txt`.
- Shows a main menu after successful login.
- Searches flights from `flights.txt` with optional filters.
- Books a selected flight and stores the booking in `bookings.txt`.
- Displays only the logged-in user's bookings.
- Allows the user to cancel one of their bookings.
- Simulates payment through card, UPI, or net banking.

## Main Components

### `main()`
The entry point that controls the application flow. It repeatedly shows the login/register menu, and after login it shows the flight management menu.

### User handling
- `registerUser()` creates a new username and password entry in `users.txt`.
- `loginUser()` checks the entered credentials against the stored user records.
- `CheckUserExist()` prevents duplicate usernames during registration.
- `CheckValidPassword()` validates password length and basic formatting rules.

### Flight handling
- `searchFlights()` reads all flights from `flights.txt` and prints only the flights that match the user's source, destination, and optional filters.
- `readFlightRecord()` parses one flight record from the file into a `struct Flight`.
- `display_flight()` formats a flight record for output.

### Booking handling
- `bookFlight()` first shows matching flights, then asks the user to choose a flight number.
- It confirms the selection, processes payment, asks for passenger name, and appends the booking to `bookings.txt`.
- `processPayment()` is a simulated payment gateway that accepts card, UPI, or net banking inputs.

### Booking display and cancellation
- `viewBookings()` reads `bookings.txt` and prints only the records that belong to the logged-in user.
- `cancelBooking()` lists the user's bookings, lets them choose one, confirms the action, and rewrites `bookings.txt` without the cancelled record.
- `readBooking()` parses one comma-separated booking record.

## File Structure
- `my_code.c` - main source file containing the current implementation.
- `main.c` - alternate/older source file in the workspace.
- `users.txt` - stored usernames and passwords.
- `flights.txt` - available flight records.
- `bookings.txt` - saved booking records.
- `TESTS/` - test-related source file(s).

## Data File Formats

### `users.txt`
Space-separated records:
```text
username password
```

Example:
```text
TomHawk tom
TejasJain tej
```

### `flights.txt`
Space-separated records in this order:
```text
flightNo from to date month year startHour startMinute endHour endMinute price
```

Example:
```text
108 Bengaluru Kochi 13 4 2026 15 30 17 05 3100
```

### `bookings.txt`
Comma-separated records in this order:
```text
username,passenger,flightNo,amount
```

Example:
```text
TomHawk,Tom Hawk,108,3100
```

## How It Works
1. The program starts and asks the user to log in or register.
2. On successful login, it stores the username for later filtering.
3. Flight search reads `flights.txt` record by record and matches the route and optional filters.
4. Booking uses the chosen flight number to locate the flight, then writes the confirmed booking to `bookings.txt`.
5. Viewing bookings reads all booking records and prints only those whose username matches the current user.
6. Cancellation loads all bookings, removes the selected record, and writes the remaining records back to the file.

## Build and Run
Compile the program with GCC:
```bash
gcc my_code.c -o a.exe
```

Run it:
```bash
./a.exe
```

On Windows PowerShell:
```powershell
.\a.exe
```

## Notes
- The application uses simple text files instead of a database.
- Input is handled with `scanf()` and `fgets()`, so the file formats must stay consistent.
- `bookings.txt` should contain valid comma-separated rows or booking-related features may fail to parse the file correctly.
