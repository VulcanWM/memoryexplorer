#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

ll_leaderboard *ll_load() {
    // loads the data from a text file and stores it in a dynamic array
    // returns the pointer to the dynamic array
    FILE *source = fopen("/Users/vulcanwm/CLionProjects/memoryexplorer/data.txt", "r");
    if (source == NULL) {
        printf("source not found");
        return NULL;
    }
    char line[100];
    ll_leaderboard *ptr = NULL;

    while (fgets(line, 100, source)) {
        char username[50];
        int score;
        sscanf(line, "%49[^,],%d", username, &score);

        ll_leaderboard *newPtr = malloc(sizeof(ll_leaderboard));
        if (newPtr == NULL) {
            printf("memory allocation failed");
            return ptr;
        }
        strcpy(newPtr->username, username);
        newPtr->score = score;
        newPtr->next = ptr;
        ptr = newPtr;
    }
    fclose(source);
    return ptr;
}

void ll_unload(ll_leaderboard *users) {
    // frees all the memory used to store the linked list
    while (users != NULL) {
        ll_leaderboard *nextPtr = users->next;
        free(users);
        users = nextPtr;
    }
}

void ll_display(ll_leaderboard *users) {
    // displays all the data contained in the linked
    while (users != NULL) {
        printf("username: %s, score: %d\n", users->username, users->score);
        users = users->next;
    }
}

ll_leaderboard *ll_add_data(ll_leaderboard *users, const char *username, const int score) {
    // adds a new data entry to the linked list
    ll_leaderboard *newPtr = malloc(sizeof(ll_leaderboard));
    if (newPtr == NULL) {
        printf("memory allocation failed");
        return users;
    }
    strcpy(newPtr->username, username);
    newPtr->score = score;
    newPtr->next = users;
    return newPtr;
}

int ll_search_data(const ll_leaderboard *users, const char *username) {
    while (users != NULL) {
        if (strcmp(users->username, username) == 0) {
            return users->score;
        }
        users = users->next;
    }
    return -1;
}

ll_leaderboard *ll_remove_data(ll_leaderboard *users, const char *username) {
    // removes the data entry for the username specified in the parameter
    if (users == NULL) return NULL;
    if (strcmp(users->username, username) == 0) {
        ll_leaderboard *newPtr = users->next;
        free(users);
        return newPtr;
    }
    ll_leaderboard *originalPointer = users;
    while (users->next != NULL) {
        if (strcmp(users->next->username, username) == 0) {
            ll_leaderboard *newPtr = users->next->next;
            free(users->next);
            users->next = newPtr;
            break;
        }
        users = users->next;
    }
    return originalPointer;
}

void ll_amend_data(ll_leaderboard *users, const char *username, const int score) {
    // amends the score of a user in the dynamic array
    while (users != NULL) {
        if (strcmp(users->username, username) == 0) {
            users->score = score;
            return;
        }
        users = users->next;
    }
}