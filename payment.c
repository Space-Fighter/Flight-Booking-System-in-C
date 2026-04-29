#include "app.h"

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