#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_PASSWORD_LENGTH 50
#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 100
#define MAX_POSITION_LENGTH 50

struct User {
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char position[MAX_POSITION_LENGTH];
    char username[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int numUsers = 0;

struct Password {
    char service[MAX_NAME_LENGTH];
    char username[MAX_PASSWORD_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Password passwords[MAX_USERS];
int numPasswords = 0;

void addUser(const char *name, const char *email, const char *position, const char *username, const char *password) {
    if (numUsers < MAX_USERS) {
        strcpy(users[numUsers].name, name);
        strcpy(users[numUsers].email, email);
        strcpy(users[numUsers].position, position);
        strcpy(users[numUsers].username, username);
        strcpy(users[numUsers].password, password);
        numUsers++;
        printf("User %s added.\n", username);
    } else {
        printf("User database is full.\n");
    }
}

int authenticate(const char *username, const char *password) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // Return the index of the authenticated user
        }
    }
    return -1; // Authentication failed
}

void addPassword(const char *service, const char *username, const char *password) {
    if (numPasswords < MAX_USERS) {
        strcpy(passwords[numPasswords].service, service);
        strcpy(passwords[numPasswords].username, username);
        strcpy(passwords[numPasswords].password, password);
        numPasswords++;
        printf("Password for %s added.\n", service);
    } else {
        printf("Password database is full.\n");
    }
}

void viewPasswords() {
    printf("\nStored Passwords:\n");
    for (int i = 0; i < numPasswords; i++) {
        printf("Service: %s\n", passwords[i].service);
        printf("Username: %s\n", passwords[i].username);
        printf("Password: %s\n", passwords[i].password);
        printf("\n");
    }
}

int main() {
    printf("Welcome to Secure 4 U Password Manager!\n");

    while (1) {
        int choice;
        printf("\nOptions:\n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char username[MAX_PASSWORD_LENGTH];
            char password[MAX_PASSWORD_LENGTH];

            printf("Enter your username: ");
            scanf("%s", username);

            printf("Enter your password: ");
            scanf("%s", password);

            int authenticatedUserIndex = authenticate(username, password);
            if (authenticatedUserIndex != -1) {
                printf("Authentication successful. Welcome, %s!\n", username);
                
                if (strcmp(users[authenticatedUserIndex].position, "admin") == 0) {
                    printf("Welcome to Secure 4 U Password Manager, Admin!\n");

                    while (1) {
                        int managerChoice;
                        printf("\nPassword Manager:\n");
                        printf("1. Add Password\n");
                        printf("2. View Passwords\n");
                        printf("3. Logout\n");
                        printf("Enter your choice: ");
                        scanf("%d", &managerChoice);

                        if (managerChoice == 1) {
                            char service[MAX_NAME_LENGTH];
                            char username[MAX_PASSWORD_LENGTH];
                            char password[MAX_PASSWORD_LENGTH];

                            printf("Enter service name: ");
                            scanf("%s", service);

                            printf("Enter username: ");
                            scanf("%s", username);

                            printf("Enter password: ");
                            scanf("%s", password);

                            addPassword(service, username, password);
                        } else if (managerChoice == 2) {
                            viewPasswords();
                        } else if (managerChoice == 3) {
                            printf("Logging out from Secure 4 U Password Manager. Goodbye!\n");
                            break;
                        } else {
                            printf("Invalid choice. Please select a valid option.\n");
                        }
                    }
                } else {
                    printf("You do not have access to Secure 4 U Password Manager. Please contact your admin!\n");
                }
            } else {
                printf("Authentication failed. Please try again.\n");
            }
        } else if (choice == 2) {
            char name[MAX_NAME_LENGTH];
            char email[MAX_EMAIL_LENGTH];
            char position[MAX_POSITION_LENGTH];
            char username[MAX_PASSWORD_LENGTH];
            char password[MAX_PASSWORD_LENGTH];
            char confirm[MAX_PASSWORD_LENGTH];

            printf("Enter your name: ");
            scanf("%s", name);
            
            printf("Enter your email: ");
            scanf("%s", email);

            printf("Enter your position: ");
            scanf("%s", position);

            printf("Enter a username: ");
            scanf("%s", username);

            printf("Enter a password: ");
            scanf("%s", password);

            printf("Confirm password: ");
            scanf("%s", confirm);

            if (strcmp(password, confirm) == 0) {
                addUser(name, email, position, username, password);
                printf("Account created successfully.\n");
            } else {
                printf("Passwords do not match. Account creation failed.\n");
            }
        } else if (choice == 3) {
            printf("Exiting Secure 4 U Password Manager. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
