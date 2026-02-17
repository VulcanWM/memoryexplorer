#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct leaderboard {
    char username[50];
    int score;
    struct leaderboard *next;
} leaderboard;

leaderboard *load();
void unload(leaderboard *users);
leaderboard *add_data(leaderboard *users, const char *username, int score);
leaderboard *remove_data(leaderboard *users, const char *username);
void amend_data(leaderboard *users, const char *username, int score);
void display(leaderboard *users);
int search_data(const leaderboard *users, const char *username);

int main() {
    leaderboard *users = load();
    printf("loaded all the data\n");
    int hi_score = search_data(users, "hi");
    printf("hi's score: %d\n", hi_score);
    amend_data(users, "hi", 123456);
    printf("changed hi's score to 123456\n");
    users = remove_data(users, "abcde");
    printf("removed user abcde\n");
    users = add_data(users, "new user", 1000);
    printf("added new user\n");
    printf("displaying the data\n");
    display(users);
    unload(users);
    printf("unloaded all the data\n");
    return 0;
}

leaderboard *load() {
    // loads the data from a text file and stores it in a dynamic array
    // returns the pointer to the dynamic array
    FILE *source = fopen("/Users/vulcanwm/CLionProjects/memoryexplorer/data.txt", "r");
    if (source == NULL) {
        printf("source not found");
        return NULL;
    }
    char line[100];
    leaderboard *ptr = NULL;

    while (fgets(line, 100, source)) {
        char username[50];
        int score;
        sscanf(line, "%49[^,],%d", username, &score);

        leaderboard *newPtr = malloc(sizeof(leaderboard));
        if (newPtr == NULL) {
            printf("memory allocation failed");
            return NULL;
        }
        strcpy(newPtr->username, username);
        newPtr->score = score;
        if (ptr == NULL) {
            ptr = newPtr;
        } else {
            leaderboard *bPointer = ptr->next;
            ptr->next = newPtr;
            newPtr->next = bPointer;
        }
    }
    fclose(source);
    return ptr;
}

void unload(leaderboard *users) {
    // frees all the memory used to store the linked list
    while (users != NULL) {
        leaderboard *nextPtr = users->next;
        free(users);
        users = nextPtr;
    }
}

void display(leaderboard *users) {
    // displays all the data contained in the linked
    while (users != NULL) {
        printf("username: %s, score: %d\n", users->username, users->score);
        users = users->next;
    }
}

leaderboard *add_data(leaderboard *users, const char *username, const int score) {
    // adds a new data entry to the linked list
    leaderboard *newPtr = malloc(sizeof(leaderboard));
    if (newPtr == NULL) {
        printf("memory allocation failed");
        return users;
    }
    if (users == NULL) {
        users = newPtr;
    } else {
        strcpy(newPtr->username, username);
        newPtr->score = score;
        leaderboard *bPointer = users->next;
        users->next = newPtr;
        newPtr->next = bPointer;
    }
    return users;
}

int search_data(const leaderboard *users, const char *username) {
    while (users != NULL) {
        if (strcmp(users->username, username) == 0) {
            return users->score;
        }
        users = users->next;
    }
    return -1;
}

leaderboard *remove_data(leaderboard *users, const char *username) {
    // removes the data entry for the username specified in the parameter
    if (users == NULL) return NULL;
    if (strcmp(users->username, username) == 0) {
        leaderboard *newPtr = users->next;
        free(users);
        return newPtr;
    }
    leaderboard *originalPointer = users;
    while (users->next != NULL) {
        if (strcmp(users->next->username, username) == 0) {
            leaderboard *newPtr = users->next->next;
            free(users->next);
            users->next = newPtr;
            break;
        }
        users = users->next;
    }
    return originalPointer;
}

void amend_data(leaderboard *users, const char *username, const int score) {
    while (users != NULL) {
        if (strcmp(users->username, username) == 0) {
            users->score = score;
            return;
        }
        users = users->next;
    }
}