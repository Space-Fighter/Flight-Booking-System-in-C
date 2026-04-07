# Viva Questions With Answers - GEU Flight Booking System

## 1. Project Overview

### 1. What is the purpose of this project?
It is a console-based flight booking system that lets a user register, log in, search flights, book a flight, view bookings, and cancel bookings.

### 2. Why did you build this project?
It demonstrates core C concepts such as structures, file handling, string handling, functions, and menu-driven program design.

### 3. Is this project database-based?
No. It stores data in plain text files such as `users.txt`, `flights.txt`, and `bookings.txt`.

### 4. What are the main modules in the program?
The main modules are user registration/login, flight search, booking, payment simulation, booking display, and cancellation.

### 5. Which file contains the main implementation?
The main implementation is in `my_code.c`, while `main.c` is another version in the workspace.

### 6. How does the program start?
It begins with a menu that asks the user to either log in, register, or exit.

### 7. What happens after login?
The user sees the main menu with flight search, booking, booking view, cancellation, and logout options.

### 8. How does the program keep track of the current user?
After login, the username is copied into a variable and passed to other functions.

### 9. Why is this project useful for viva?
It covers many standard C concepts in a single working application.

### 10. What is the overall workflow of the system?
Login or register first, then search and book flights, then view or cancel bookings as needed.

## 2. Structures

### 11. Why are structures used in this project?
Structures group related data together, making the code cleaner and easier to manage.

### 12. What does `struct Date` store?
It stores `date`, `month`, and `year` values.

### 13. What does `struct Time` store?
It stores `hour` and `minute` values.

### 14. What does `struct Flight` store?
It stores flight number, source, destination, date, start time, end time, and price.

### 15. What does `struct Booking` store?
It stores the username, passenger name, flight number, and amount paid.

### 16. Why is `struct Flight` useful?
It represents one complete flight record in a single data type.

### 17. Why are `Date` and `Time` separate structures?
They keep date and time data organized and reusable.

### 18. What is a nested structure?
A structure containing another structure as a member.

### 19. Is `struct Flight` a nested structure?
Yes, because it contains `struct Date` and `struct Time` members.

### 20. What is the benefit of using a structure instead of separate variables?
It keeps related values together and makes function arguments simpler.

### 21. Can one structure be assigned to another?
Yes, structure assignment is allowed if both variables are of the same type.

### 22. What is the difference between a structure and an array?
An array stores same-type elements, while a structure can store different data types together.

## 3. User Registration and Login

### 23. What does `registerUser()` do?
It collects a username and password and appends them to `users.txt`.

### 24. What does `loginUser()` do?
It checks whether the entered username and password match a record in `users.txt`.

### 25. Why do you use `users.txt`?
It stores registered user credentials persistently.

### 26. What is the format of `users.txt`?
It uses space-separated values: `username password`.

### 27. What does `CheckUserExist()` do?
It checks whether the entered username already exists.

### 28. Why is duplicate username checking needed?
It prevents two users from registering with the same login name.

### 29. What does `CheckValidPassword()` check?
It checks password length and whether spaces are allowed.

### 30. Why should usernames not contain spaces?
Because the file format and input parsing expect a single token.

### 31. Why should passwords not contain commas?
To avoid breaking file formats and parsing logic.

### 32. Why is `strcmp()` used in login?
Because strings in C cannot be compared with `==`.

### 33. What does `strcpy(username, user)` do?
It copies the logged-in username into the caller’s buffer.

### 34. What happens if login fails?
The program prints an error message and returns to the main screen.

### 35. What happens if `users.txt` cannot be opened?
Login or registration cannot continue properly.

### 36. Why is file-based login insecure in real systems?
Passwords are stored in plain text and are not encrypted.

## 4. Flight Search

### 37. What does `searchFlights()` do?
It reads flight records from `flights.txt` and displays matching flights.

### 38. What is the format of `flights.txt`?
It is space-separated with flight number, cities, date, time, and price fields.

### 39. Why is `readFlightRecord()` used?
It centralizes flight-file parsing in one helper function.

### 40. Why is a helper function better here?
It avoids repeating the same `fscanf()` logic in multiple places.

### 41. How does flight search compare cities?
It uses `strcmp()` on `from` and `to` strings.

### 42. Why are optional filters used?
They allow searching by date, time, or price when needed.

### 43. How is date filtering done?
The entered date is compared with the flight’s stored date fields.

### 44. How is time filtering done?
The entered time is compared with the flight’s start time.

### 45. How is price filtering done?
The flight price is checked against the entered minimum and maximum range.

### 46. What does `display_flight()` print?
It prints flight number, source, destination, date, time, and price in a readable format.

### 47. What happens if no flights match?
The program prints `No flights found!`.

### 48. Why is `fopen("flights.txt", "r")` used?
Because the file is only being read, not written.

### 49. Why is `getchar()` used after `scanf()`?
It removes the leftover newline from the input buffer.

### 50. What is the benefit of displaying flights before booking?
It lets the user confirm the correct flight number visually.

## 5. Booking

### 51. What does `bookFlight()` do?
It lets the user choose a flight and stores the confirmed booking.

### 52. Why does `bookFlight()` call `searchFlights()` first?
So the user can see available matching flights before choosing one.

### 53. How is the flight selected for booking?
The user enters a flight number, and the program searches for it in `flights.txt`.

### 54. What happens after a flight is found?
The program shows the flight details and asks for confirmation.

### 55. Why is confirmation needed?
It avoids accidental bookings.

### 56. Why is payment processed before writing the booking?
To ensure the booking is stored only after successful payment.

### 57. What does `processPayment()` do?
It simulates a payment gateway and returns success or failure.

### 58. What payment methods are supported?
Card, UPI, and net banking.

### 59. What happens if payment fails?
The booking is cancelled and not written to the file.

### 60. What happens if the user declines booking confirmation?
The program prints that the booking was cancelled by the user.

### 61. What is written to `bookings.txt` after success?
The username, passenger name, flight number, and amount, separated by commas.

### 62. Why is `bookings.txt` opened in append mode?
So new bookings are added without deleting old ones.

### 63. Why is the passenger name stored separately from the username?
Because the passenger may be different from the account holder.

### 64. What happens if the entered flight number does not exist?
No valid flight is selected, so booking should not proceed correctly.

### 65. Why is `scanf("%d", &flightNo)` used here?
Because flight numbers are numeric values.

## 6. Payment Simulation

### 66. What is `processPayment()` in this project?
It is a mock payment system, not a real payment integration.

### 67. Why was payment kept simple?
Because the goal is to demonstrate logic flow, not real payment processing.

### 68. How does card payment validation work?
It checks the card number length, CVV length, and expiry input.

### 69. How does UPI payment validation work?
It checks whether the UPI ID contains `@`.

### 70. How does net banking validation work?
It checks whether the account number length is valid.

### 71. What does `strlen()` do in payment validation?
It measures the length of entered strings.

### 72. Why is `strchr()` used for UPI ID checking?
It checks whether the `@` symbol exists in the entered string.

## 7. Viewing and Cancelling Bookings

### 73. What does `viewBookings()` do?
It prints only the bookings belonging to the logged-in user.

### 74. Why does it show only one user’s bookings?
Because it filters records using the stored username.

### 75. What does `readBooking()` parse?
It parses one comma-separated booking record from `bookings.txt`.

### 76. Why is `bookings.txt` comma-separated?
So each booking field is clearly separated during parsing.

### 77. What does `cancelBooking()` do?
It lists the user’s bookings and removes the selected one from the file.

### 78. Why are all bookings loaded into memory before cancellation?
Because the file must be rewritten after removing one record.

### 79. Why does `cancelBooking()` keep a separate index list?
To map the user’s visible booking number to the actual array index.

### 80. Why is the file rewritten after cancellation?
Because text files do not support deleting a single line directly.

### 81. What does `fopen("bookings.txt", "w")` do?
It truncates the file and opens it for writing fresh content.

### 82. What happens if the user cancels nothing?
The original file remains unchanged.

### 83. Why is a cancellation confirmation asked?
To prevent accidental deletion of a booking.

## 8. File Handling Concepts

### 84. What is a file pointer?
It is a pointer of type `FILE *` used to access files in C.

### 85. What is the syntax of `fopen()`?
`FILE *fopen(const char *filename, const char *mode);`

### 86. What file modes are used in this project?
`r`, `a`, `a+`, and `w`.

### 87. What does read mode do?
It opens a file for reading only.

### 88. What does append mode do?
It adds new content at the end of the file.

### 89. What does write mode do?
It creates or overwrites the file content.

### 90. What does `fclose()` do?
It closes an open file and releases resources.

### 91. What does `fscanf()` do?
It reads formatted input from a file.

### 92. What does `fprintf()` do?
It writes formatted output to a file.

### 93. Why are text files used here?
They are simple to read, write, and debug in a small project.

### 94. What is EOF?
EOF means end of file, used to detect when reading is finished.

### 95. What happens if a file is not closed properly?
Data may not be saved correctly and resources can leak.

## 9. String Handling

### 96. Why are character arrays used for strings in C?
Because C does not have a built-in string type like some higher-level languages.

### 97. What does `fgets()` do?
It safely reads a line of text from input or a file.

### 98. Why is `fgets()` safer than `gets()`?
Because it limits the number of characters read.

### 99. What does the `readStr` macro do?
It calls `fgets()` and then removes the trailing newline.

### 100. Why is the newline removed after `fgets()`?
Because `fgets()` keeps the newline if space is available.

### 101. What does `strcspn()` do in `readStr`?
It finds the position of the newline so it can be replaced with `\0`.

### 102. Why is `strcmp()` used instead of `==`?
Because `==` compares addresses, not string contents.

### 103. What does `strchr()` do?
It searches a string for a character.

### 104. What does `strcpy()` do?
It copies one string into another.

### 105. What does `strlen()` do?
It returns the length of a string.

### 106. What is a null-terminated string?
It is a character array ending with `\0`.

### 107. What is buffer overflow?
It happens when more data is written than the array can hold.

### 108. How does this project reduce buffer overflow risk?
By using fixed-size buffers with `fgets()` and careful field sizes.

## 10. Input/Output and Control Flow

### 109. Why are `scanf()` and `fgets()` both used?
`scanf()` is used for numbers and `fgets()` is used for strings with spaces.

### 110. Why is `getchar()` used after `scanf()`?
To consume leftover newline characters.

### 111. What problem can happen when mixing `scanf()` and `fgets()`?
`fgets()` may read the leftover newline instead of fresh input.

### 112. What does `while (1)` mean?
It creates an infinite loop until broken by `return`, `break`, or `goto`.

### 113. Why is a `switch` used in the menu?
It cleanly handles multiple menu choices.

### 114. What does `break` do?
It exits the current loop or switch block.

### 115. What does `return` do?
It exits the current function.

### 116. What is the role of `goto logout;` here?
It exits the inner menu loop and returns to the main login screen.

### 117. Why is `printf()` used so often?
To display prompts, menus, and results to the user.

### 118. What is formatted output?
It is output produced using format specifiers like `%d` and `%s`.

## 11. Error Handling and Edge Cases

### 119. What happens if `users.txt` is missing?
Login or registration may fail unless the file is created.

### 120. What happens if `flights.txt` is missing?
Flight search and booking cannot work.

### 121. What happens if `bookings.txt` is missing?
Viewing or canceling bookings cannot work properly.

### 122. What happens if no booking exists for the user?
The program prints `No bookings found.`.

### 123. What happens if the payment method is invalid?
The payment fails and the booking is cancelled.

### 124. What happens if the entered card number is too short?
Card payment is rejected.

### 125. What happens if the CVV is invalid?
Card payment is rejected.

### 126. What happens if the UPI ID is invalid?
UPI payment is rejected.

### 127. What happens if the account number is too short?
Net banking payment is rejected.

### 128. What is the limitation of fixed-size arrays like `all[100]`?
They can overflow if the file contains more than 100 relevant records.

## 12. C Language Concepts

### 129. What is a function prototype?
It is a function declaration that tells the compiler the function name, return type, and parameters.

### 130. Why are function declarations written before `main()`?
So the compiler knows about the functions before they are called.

### 131. What is the difference between declaration and definition?
A declaration tells the compiler a function exists, while a definition provides the code.

### 132. What is a pointer?
It is a variable that stores the address of another variable.

### 133. Why are pointers used with files?
Because file functions work with `FILE *` pointers.

### 134. What does `struct Flight *f` mean?
It means `f` is a pointer to a `struct Flight`.

### 135. What does the `->` operator do?
It accesses structure members through a pointer.

### 136. What is the difference between `.` and `->`?
`.` is used with a structure variable, and `->` is used with a structure pointer.

### 137. What is pass-by-value?
It means the function receives a copy of the argument.

### 138. Why use `char username[]` as a parameter?
Because arrays decay to pointers when passed to functions.

### 139. What is a macro?
It is a preprocessor replacement rule.

### 140. Why is `readStr` a macro?
It wraps repeated input logic into one reusable block.

### 141. What are preprocessor directives?
They are instructions processed before compilation, such as `#include`.

### 142. What is the role of `#include <stdio.h>`?
It provides declarations for input/output functions like `printf()` and `scanf()`.

### 143. What is the role of `#include <string.h>`?
It provides string-handling functions like `strcmp()`, `strlen()`, and `strcpy()`.

### 144. What is the role of `#include <stdlib.h>`?
It provides general utility functions and memory-related helpers.

### 145. What is variable scope?
Scope is the region where a variable can be accessed.

### 146. What is the lifetime of a local variable?
It exists only while the function is executing.

### 147. What is recursion?
It is a function calling itself; this project does not use recursion.

### 148. What is an array of structures?
It is a collection of structure variables stored in array form.

## 13. Data Design and Improvement Questions

### 149. Why is `users.txt` space-separated?
Because the program reads it with `fscanf("%s %s")`.

### 150. Why is `bookings.txt` comma-separated?
Because `readBooking()` parses it using comma delimiters.

### 151. Why is file format consistency important?
Because the parsing logic depends on it.

### 152. What is the advantage of one record per line?
It makes file reading and rewriting simpler.

### 153. What is a limitation of plain-text storage?
It is less secure and less scalable than a database.

### 154. How could this project be improved?
By adding better validation, real authentication, and database storage.

### 155. How would you make passwords more secure?
By hashing them instead of storing plain text.

### 156. How would you prevent duplicate bookings?
By checking if the same user already booked the same flight.

### 157. How would you add seat selection?
By storing seat data in the booking record.

### 158. How would you make the code more modular?
By splitting it into separate source files for users, flights, and bookings.

### 159. How would you add sorting by price or time?
By loading flight records into memory and applying a sorting algorithm.

### 160. What future improvement would you suggest?
Use a database, add admin features, and improve error handling.

## 14. Quick Revision Answers

### 161. What does `loginUser()` return on success?
It returns `1`.

### 162. What does `loginUser()` return on failure?
It returns `0`.

### 163. What does `strcmp()` return when strings are equal?
It returns `0`.

### 164. What does `fopen()` return on failure?
It returns `NULL`.

### 165. What does `fscanf()` return when reading succeeds?
It returns the number of matched input items.

### 166. What does `strchr()` return when the character is not found?
It returns `NULL`.

### 167. Which file stores login credentials?
`users.txt`.

### 168. Which file stores flight data?
`flights.txt`.

### 169. Which file stores bookings?
`bookings.txt`.

### 170. What does `display_date()` do?
It prints a date in `DD/MM/YYYY` format.

### 171. What does `display_time()` do?
It prints a time in `HH:MM` format.

### 172. What does `display_flight()` do?
It prints full flight details in one line.

### 173. What is the main menu option for booking?
Option `2`.

### 174. What is the main menu option for viewing bookings?
Option `3`.

### 175. What is the main menu option for cancellation?
Option `4`.

### 176. What is the main menu option for logout?
Option `5`.

## 15. Oral Follow-Up Questions

### 177. Can you explain the full booking flow?
Yes. The user logs in, searches flights, chooses a flight number, confirms it, pays, and then the booking is saved.

### 178. Can you explain why `strcmp()` is necessary?
Yes. Strings must be compared by content, not by address.

### 179. Can you explain why cancellation rewrites the file?
Yes. Removing a single line from a text file usually requires rewriting the remaining records.

### 180. Can you explain why structures are important in this project?
Yes. They keep related data together and make file parsing and function design easier.

### 181. Can you explain why `fgets()` is used in `readStr`?
Yes. It safely reads full lines, including spaces, and avoids overflow issues better than `gets()`.
