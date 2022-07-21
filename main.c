//Mohammad Ali Mirzaaee 400109481
//Mohammad Amin Tayebi  400105111


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAX_USER_MESSAGE_NUMBER 100
#define MAX_USER_NUMBER 100
#define MAX_MESSAGE_NUMBER 10000
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100
#define MAX_MESSAGE_LENGTH 1000

int messageIDCounter = 1;
int userIDCounter = 1;
FILE *counterFile;
typedef struct {
    int UserID;
    char *username;
    char *password;
    int messageID[MAX_USER_MESSAGE_NUMBER];
    int messageNum;
} User;

typedef struct {
    int messageID;
    char *text;
    int writerID;
} Message;

User allUsers[MAX_USER_NUMBER];
Message *allMessages[MAX_MESSAGE_NUMBER];

void newUser(char *username, char *password);

void loginMenu();

void mainMenu(int userID);

void sendMessageMenu(int id);

void editMessageMenu(int userID);

void viewAllMessagesMenu();

void changePasswordMenu(int userID);

void handleShowAllMessages();

void handleEditMessage(int userID);

void newMessage(int userID);

void openFiles();


void handleChangePassword(int userID);

int main() {
    openFiles();
    loginMenu();

    return 0;
}

void openFiles() {
    counterFile = fopen("counterFile.txt", "r");
    if (counterFile == NULL) {
        printf("null e\n");
    } else {
        messageIDCounter = getw(counterFile);
        printf("ok e counter: %d\n", messageIDCounter);
    }
    fclose(counterFile);
    counterFile = fopen("counterFile.txt", "w+");

}

void loginMenu() {

    char *username = (char *) malloc(sizeof(char) * MAX_USERNAME_LENGTH);
    char *password = (char *) malloc(sizeof(char) * MAX_PASSWORD_LENGTH);
    int registerUser;
    while (1) {
        registerUser = 1;
        printf("Enter Your Username:");
        scanf("%s", username);
        printf("Enter Your Password:");
        scanf("%s", password);

        printf("1.Login\n");
        printf("2.Register\n");
        printf("Enter the number of the action:");
        int numberOfAction;
        scanf("%d", &numberOfAction);
        if (numberOfAction == 1) {

            int userNotExists = 1;
            for (int i = 0; i < userIDCounter - 1; ++i) {
                if (strcmp(username, allUsers[i].username) == 0) {
                    userNotExists = 0;
                    if (strcmp(password, allUsers[i].password) == 0) {
                        printf("Welcome %s!\n", username);
                        mainMenu(i);
                        break;
                    } else {

                        printf("Username & Password don't match!\n");
                        break;
                    }
                }
            }
            if (userNotExists) {
                printf("No Username matches\'%s\'\n", username);
            }

        } else if (numberOfAction == 2) {
            int canRegister = 1;
            for (int i = 0; i < userIDCounter - 1; ++i) {
                if (strcmp(username, allUsers[i].username) == 0) {
                    canRegister = 0;
                    printf("Username \'%s\' already exists\n", username);
                    break;
                }
            }
            if (canRegister) {
                printf("Register successful %s, welcome!\n", username);
                newUser(username, password);

                mainMenu(userIDCounter - 2);
            }
        } else {
            printf("Entered wrong number\n");
        }


//        for (int i = 0; i < userIDCounter - 1; i++) {
//            if (strcmp(allUsers[i]->username, username) == 0) {
//                registerUser = 0;
//                if (strcmp(allUsers[i]->password, password) == 0) {
//                    printf("Login\n");
//                    mainMenu(i);
//                    break;
//                } else {
//                    printf("Incorrect Password\n");
//                    break;
//                }
//            }
//        }
//        if (registerUser) {
//            newUser(username, password);
//            mainMenu(userIDCounter - 2);
//        }
    }
}

void newUser(char *username, char *password) {
    User *user = malloc(sizeof(User));
    user->username = malloc(sizeof(char) * MAX_USERNAME_LENGTH);
    user->password = malloc(sizeof(char) * MAX_PASSWORD_LENGTH);
    user->messageNum = 0;
    strcpy(user->password, password);
    strcpy(user->username, username);
    user->UserID = userIDCounter;
    allUsers[userIDCounter - 1] = *user;
    userIDCounter++;
}

void newMessage(int userID) {
    printf("Enter Your Message:\n");
    allMessages[messageIDCounter - 1] = malloc(sizeof(Message));
    allMessages[messageIDCounter - 1]->text = (char *) malloc(sizeof(char) * MAX_MESSAGE_LENGTH);
    allMessages[messageIDCounter - 1]->writerID = userID;
    scanf("\n%[^\n]%*c", allMessages[messageIDCounter - 1]->text);
    allUsers[userID].messageID[allUsers[userID].messageNum] = messageIDCounter++ - 1;
    allUsers[userID].messageNum++;
    putw(messageIDCounter, counterFile);
    printf("in file:\n\n");
    fprintf(counterFile, "%d\n");
    printf("Message Sent\n\n");

}

void mainMenu(int userID) {
    int state = 1;

    while (state) {
        printf("Main Menu:\n\n");
        printf("1.Send Message\n");
        printf("2.Edit Message\n");
        printf("3.View All Message\n");
        printf("4.Change Password\n");
        printf("5.Exit\n");
        printf("\nEnter Number Of Menu:");

        int num;
        scanf("%d", &num);
        switch (num) {

            case 1: {
                sendMessageMenu(userID);
                break;
            }
            case 2: {
                editMessageMenu(userID);
                break;
            }
            case 3: {
                viewAllMessagesMenu();
                break;
            }
            case 4: {
                changePasswordMenu(userID);
                break;
            }
            case 5: {
                state = 0;
                break;
            }
            default: {
                printf("Entered Wrong Number\n");
                break;
            }
        }
    }
}

void changePasswordMenu(int userID) {

    int state = 1;
    while (state) {
        printf("Change Password Menu\n");
        printf("1.change Password\n");
        printf("2.Exit\n");
        printf("Enter Number Of Menu:");
        int order;
        scanf("%d", &order);

        switch (order) {
            case 1: {
                handleChangePassword(userID);
                break;
            }
            case 2: {
                state = 0;
                break;
            }
            default: {
                printf("Entered Wrong Number\n");
                break;
            }
        }
    }
}

void handleChangePassword(int userID) {
    printf("Enter Your New Password:");
    scanf("%s", allUsers[userID].password);
    printf("%s\n", allUsers[userID].password);
    printf("Password Changed\n");

}

void viewAllMessagesMenu() {
    int state = 1;
    while (state) {
        printf("1.View All Messages\n");
        printf("2.Exit\n");
        printf("\nEnter Number Of Menu:");
        int order;
        scanf("%d", &order);
        switch (order) {

            case 1: {

                handleShowAllMessages();
                break;
            }

            case 2: {
                state = 0;
                break;
            }

            default: {
                printf("Entered Wrong Number\n");
                break;
            }
        }
    }
}

void handleShowAllMessages() {

    printf("------------------------\n");
    for (int i = 0; i < messageIDCounter - 1; ++i) {
        {
            printf("%d.%s", i + 1, allMessages[i]->text);
            printf("\n------------------------\n");
        }
    }
}

void editMessageMenu(int userID) {

    int state = 1;
    while (state) {
        printf("Edit Message Menu:\n");
        printf("1.Edit Message\n");
        printf("2.Exit\n");
        printf("Enter Number Of Menu:");
        int order;
        scanf("%d", &order);

        switch (order) {
            case 1: {
                handleEditMessage(userID);
                break;
            }
            case 2: {
                state = 0;
                break;
            }
            default: {
                printf("\nEntered Wrong Number\n");
                break;
            }
        }
    }
}

void handleEditMessage(int userID) {
    printf("Enter Your Message ID:");
    int messageID;
    scanf("%d", &messageID);
    if (messageID > messageIDCounter - 1) {
        printf("No Message!\n");
    } else {
        if (allMessages[messageID - 1]->writerID != userID) {
            printf("You Can't Edit This Message!\n");
        } else {
            printf("Original Message:\n");
            printf("%s\n", allMessages[messageID - 1]->text);
            printf("\nEnter Edited Message:\n");
            scanf("\n%[^\n]%*c", allMessages[messageID - 1]->text);
            printf("\nYour Message Edited\n");

        }
    }
}

void sendMessageMenu(int userID) {
    int state = 1;

    while (state) {
        printf("Send Message Menu:\n\n");
        printf("1.Send Message\n");
        printf("2.Exit\n");
        printf("Enter Number Of Menu:");
        int order;
        scanf("%d", &order);

        switch (order) {
            case 1: {
                newMessage(userID);
                break;
            }
            case 2: {
                state = 0;
                break;
            }
            default: {
                printf("\nEntered Wrong Number\n");
                break;
            }
        }
    }
}