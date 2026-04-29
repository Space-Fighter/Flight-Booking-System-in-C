#include "app.h"
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
    if (strchr(password, ',') != NULL) {
        printf("Password cannot contain commas!\n");
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

    if (!CheckValidPassword(password)) {
        fclose(fp);
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
            fclose(fp);
            strcpy(username, user);
            return 1; // user exists
        }
    }
    fclose(fp);
    printf("Invalid Username or Password!\n");
    return 0;
}