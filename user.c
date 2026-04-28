#include "app.h"

int CheckUserExist(char username[], FILE *fp) {
    if (strchr(username, ' ') != NULL) {
        printf("Username cannot contain spaces!\n");
        return 1;
    }
    char file_user[100], file_pass[100];
    while (fscanf(fp, "%s %s", file_user, file_pass) != EOF) {
        if (strcmp(file_user, username) == 0) {
            printf("Username already exists!\n");
            return 1;
        }
    }
    return 0;
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

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("Registration Successful!\n");
}

int loginUser(char username[]) {
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
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid Username or Password!\n");
    return 0;
}