#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 20

// Define a struct within a union to store user information
union UserInfo {
    struct {
        char username[MAX_USERNAME_LENGTH];
        int isActive;  // Activation flag: 1 for true, 0 for false
    } userData;
};

int main(void) {
    union UserInfo* users = NULL;
    int userCount = 0;

    while (1) {
        printf("Enter 'create' to add a new user or 'access' to log in: ");
        char choice[10];
        fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = '\0';  // Remove the trailing newline from fgets

        if (strcmp(choice, "create") == 0) {
            char newUser[MAX_USERNAME_LENGTH];
            printf("Enter a new username: ");
            fgets(newUser, sizeof(newUser), stdin);
            newUser[strcspn(newUser, "\n")] = '\0';

            int userExists = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(newUser, users[i].userData.username) == 0) {
                    printf("Username already taken. Registration unsuccessful.\n");
                    userExists = 1;
                    break;
                }
            }

            if (!userExists) {
                users = (union UserInfo*)realloc(users, (userCount + 1) * sizeof(union UserInfo));
                strcpy(users[userCount].userData.username, newUser);

                // Prompt user to set the activation flag
                printf("Set activation flag (1 for true, 0 for false): ");
                scanf("%d", &users[userCount].userData.isActive);

                getchar();  // Consume the newline character left in the buffer

                userCount++;
                printf("User created successfully.\n");
            }
        } else if (strcmp(choice, "access") == 0) {
            char user[MAX_USERNAME_LENGTH];
            printf("Enter your username: ");
            fgets(user, sizeof(user), stdin);
            user[strcspn(user, "\n")] = '\0';

            int userFound = 0;
            for (int i = 0; i < userCount; i++) {
                if (strcmp(user, users[i].userData.username) == 0) {
                    userFound = 1;

                    // Check the activation flag before granting access
                    if (users[i].userData.isActive) {
                        printf("Access granted. Welcome, %s!\n", user);
                    } else {
                        printf("Access denied. User is not active.\n");
                    }
                    break;
                }
            }

            if (!userFound) {
                printf("Access denied. User not found.\n");
            }
        } else {
            printf("Invalid choice. Please enter 'create' or 'access'.\n");
        }
    }

    // Free allocated memory before exiting
    free(users);

    return 0;
}
