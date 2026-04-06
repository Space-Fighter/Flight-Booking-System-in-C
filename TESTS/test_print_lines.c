#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char username[100], password[100];
    FILE *fp = fopen("users.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }

    printf("All users:\n");
    while (fscanf(fp, "%s %s", username, password) == 2) {
        printf("username='%s', password='%s'\n", username, password);
    }

    fclose(fp);
    return 0;
}