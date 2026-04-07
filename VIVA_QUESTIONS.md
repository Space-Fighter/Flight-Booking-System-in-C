# Viva Questions - GEU Flight Booking System

## A. Project Overview Questions
1. What is the purpose of this flight booking system?
2. What problem does this project solve?
3. Is this project menu-driven or event-driven?
4. Why did you choose a file-based approach instead of a database?
5. What are the main modules in your program?
6. What are the major features provided by the application?
7. Which file contains the main implementation?
8. What is the role of `main()` in your program?
9. How does the program maintain user session after login?
10. What happens when the user logs out?

## B. Structure and Data Modeling Questions
11. Why did you use structures in this project?
12. What is the purpose of `struct Date`?
13. What is the purpose of `struct Time`?
14. What fields are stored in `struct Flight`?
15. What fields are stored in `struct Booking`?
16. Why is `struct Flight` a nested structure?
17. What is the advantage of storing date and time as separate structures?
18. Why is `flightNo` stored as an integer?
19. Why is `username` stored as a character array instead of a single character?
20. What is the memory layout of a structure?
21. What is structure padding?
22. How is a structure different from an array?
23. How is a structure different from a union?
24. Can you assign one structure variable to another directly?
25. Can a structure contain another structure? Why is that useful?

## C. User Registration and Login Questions
26. What does `registerUser()` do?
27. What does `loginUser()` do?
28. Why do you use `users.txt` in the login system?
29. What is the file format of `users.txt`?
30. Why did you store username and password as plain text in this project?
31. What does `CheckUserExist()` check?
32. What does `CheckValidPassword()` validate?
33. Why should usernames not contain spaces?
34. Why should passwords not contain commas in your implementation?
35. Why do you use `strcmp()` for login validation?
36. What does `strcpy(username, user)` do after successful login?
37. What happens if the username or password is incorrect?
38. What happens if `users.txt` cannot be opened?
39. Why is file validation important before reading user records?
40. How would you improve password security in a real system?

## D. Flight Search Questions
41. What does `searchFlights()` do?
42. What is the file format of `flights.txt`?
43. Why is `readFlightRecord()` used?
44. Why do you use a helper function to read flight records?
45. How does the program compare source and destination cities?
46. What is the purpose of optional filters in search?
47. How is date filtering implemented?
48. How is time filtering implemented?
49. How is price filtering implemented?
50. What does `display_flight()` print?
51. Why does the search function use `strcmp()` instead of `==` for city names?
52. What happens if no matching flight is found?
53. How does the program handle multiple matching flights?
54. Why is `fopen("flights.txt", "r")` used here?
55. What would happen if the flight file format is incorrect?
56. Why do you call `getchar()` after `scanf()` in the menu flow?

## E. Booking Questions
57. What does `bookFlight()` do?
58. Why does booking call `searchFlights()` first?
59. How is the flight number selected by the user?
60. How does the program find the selected flight in the file?
61. What happens after the flight is selected?
62. What does the confirmation prompt do?
63. Why is payment processed before storing the booking?
64. What does `processPayment()` simulate?
65. What payment methods are available in your implementation?
66. How is the passenger name stored?
67. What gets written into `bookings.txt` after a successful booking?
68. Why is `bookings.txt` opened in append mode?
69. What happens if payment fails?
70. What happens if the user declines confirmation?
71. How does the program ensure the booking amount matches the selected flight?
72. What happens if the flight number entered does not exist?
73. Why is `scanf("%d", &flightNo)` used for flight number input?

## F. Booking Display and Cancellation Questions
74. What does `viewBookings()` do?
75. Why does `viewBookings()` show only the logged-in user’s bookings?
76. What does `readBooking()` parse?
77. What is the format of a booking record in `bookings.txt`?
78. Why is comma-separated parsing used for bookings?
79. What does `cancelBooking()` do?
80. Why are all bookings loaded into an array before cancellation?
81. Why does the program keep a separate list of the current user’s booking indexes?
82. Why is the bookings file rewritten after cancellation?
83. What does `fopen("bookings.txt", "w")` do differently from append mode?
84. What happens if the user selects an invalid cancellation option?
85. Why is a confirmation step necessary before deleting a booking?
86. What happens if there are no bookings for the logged-in user?
87. How is the cancelled record skipped when rewriting the file?
88. What are the risks of using fixed-size arrays for bookings?

## G. File Handling Questions
89. What is a file pointer in C?
90. What is the syntax of `fopen()`?
91. What are the file modes used in your program?
92. What is the difference between read mode, write mode, and append mode?
93. What does `fclose()` do?
94. What is the purpose of `fscanf()`?
95. What is the purpose of `fprintf()`?
96. Why are files used for persistence in this project?
97. What is the difference between text files and binary files?
98. What happens if a file is not closed properly?
99. What is file truncation?
100. Why is `rewind()` sometimes used when reading files multiple times?
101. What is the meaning of EOF in file processing?
102. What are the dangers of assuming file data is always valid?
103. How would you detect malformed records while reading a file?

## H. String Handling Questions
104. Why do you use character arrays for names and passwords?
105. What does the `readStr` macro do?
106. Why is `fgets()` safer than `scanf("%s", ...)` for reading full strings?
107. What does `strcspn()` do in `readStr`?
108. Why is the newline removed after `fgets()`?
109. What is the role of `strcmp()`?
110. What is the role of `strchr()`?
111. What is the role of `strlen()`?
112. What is the role of `strcpy()`?
113. Why can string comparisons not be done with `==` in C?
114. What is a null-terminated string?
115. What happens if a string buffer is too small?
116. What is buffer overflow?
117. How do you avoid buffer overflow in this project?
118. What is the difference between `fgets()` and `gets()`?

## I. Input and Output Questions
119. Why do you use `scanf()` for numbers and `fgets()` for strings?
120. Why do you call `getchar()` after `scanf()`?
121. What problem occurs when mixing `scanf()` and `fgets()`?
122. How does the program print dates in `DD/MM/YYYY` format?
123. How does the program print time in `HH:MM` format?
124. Why are leading zeros used in date and time output?
125. What is formatted output in C?
126. What is the difference between console input and file input?

## J. Control Flow Questions
127. Why do you use nested loops in the menu system?
128. What is the use of `switch` in the main menu?
129. What does `goto logout;` do in your program?
130. Why is `while (1)` used in menu loops?
131. What is the effect of `break` inside a loop?
132. What is the effect of `return` inside a function?
133. What is the difference between `break`, `continue`, and `return`?
134. What is the difference between an `if` statement and a `switch` statement?

## K. Error Handling and Edge Cases
135. What happens if `users.txt` does not exist?
136. What happens if `flights.txt` does not exist?
137. What happens if `bookings.txt` does not exist?
138. How does the program handle invalid menu input?
139. How does the program handle invalid payment method selection?
140. What happens if the card number length is incorrect?
141. What happens if the CVV length is incorrect?
142. What happens if the UPI ID does not contain `@`?
143. What happens if the account number is too short?
144. What happens if a flight search returns no results?
145. What happens if `confirm` is not `y` or `Y` during booking?
146. What happens if the user enters an out-of-range booking cancellation choice?
147. What are the limitations of using fixed-size arrays like `all[100]`?
148. What happens if there are more than 100 bookings?

## L. C Language Concept Questions
149. What is the meaning of `int`, `char`, and `FILE` in C?
150. What is a function prototype?
151. Why are function declarations written before `main()`?
152. What is the difference between a function declaration and a function definition?
153. What is a pointer?
154. Why are pointers used with file handling functions?
155. What does `struct Flight *f` mean in `readFlightRecord()`?
156. What is the purpose of the `->` operator?
157. What is the difference between `.` and `->`?
158. What is pass-by-value in C?
159. Why is `char username[]` used as a function parameter?
160. What happens when an array is passed to a function?
161. What is a macro?
162. Why is `readStr` defined as a macro instead of a function?
163. What are preprocessor directives?
164. What is the role of `#include <stdio.h>`?
165. What is the role of `#include <string.h>`?
166. What is the role of `#include <stdlib.h>`?
167. What is the difference between local and global variables?
168. What is variable scope?
169. What is the lifetime of a local variable?
170. What is recursion, and is it used in this project?
171. What is an array of structures?
172. What is the difference between static and dynamic memory allocation?

## M. File Format and Data Design Questions
173. Why is `users.txt` space-separated?
174. Why is `bookings.txt` comma-separated?
175. Why is `flights.txt` space-separated?
176. What happens if the file delimiter does not match the parsing format?
177. Why is consistency in file format important?
178. What is the advantage of storing each record on a single line?
179. What are the disadvantages of plain-text storage?
180. How would you migrate this project to a database?

## N. Testing and Debugging Questions
181. How did you test the login functionality?
182. How did you test flight searching?
183. How did you test booking creation?
184. How did you test viewing bookings?
185. How did you test cancellation?
186. How would you debug a file parsing failure?
187. How would you debug incorrect string comparison behavior?
188. How would you debug a problem caused by leftover newline characters?
189. How would you verify that a booking was written correctly?
190. What tools or compiler flags can help catch C errors?

## O. Improvement and Extension Questions
191. How would you add admin functionality?
192. How would you add seat selection?
193. How would you prevent duplicate bookings?
194. How would you implement real payment integration?
195. How would you support multiple cities with the same route on different dates?
196. How would you add sorting by price or time?
197. How would you add a booking history screen?
198. How would you make usernames and passwords more secure?
199. How would you make the code more modular?
200. What future improvements would you suggest for this project?

## P. Rapid Revision Questions
201. What is a structure in C?
202. What is the purpose of `fopen()`?
203. What does `strcmp()` return when strings are equal?
204. What is the use of `fprintf()`?
205. Why is `fgets()` preferred for string input?
206. What does `readBooking()` parse?
207. Which file stores flight data?
208. Which file stores login credentials?
209. Which file stores booking records?
210. What is the return value of `loginUser()` on success?

## Q. Suggested Oral Follow-Up Questions
211. Can you explain the full booking flow from login to payment?
212. Can you explain how your file formats support the program logic?
213. Can you explain why `strcmp()` is necessary in your program?
214. Can you explain why the booking file is rewritten during cancellation?
215. Can you explain the role of each structure with an example?
