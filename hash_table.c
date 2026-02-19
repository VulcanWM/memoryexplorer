#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

int ht_get_bucket(const char *username) {
    // get the bucket of the hash table from the first letter of the username
    return tolower(username[0]) - 'a';
}

void ht_load(ht_leaderboard *table[26]) {
    // loads the data from a text file and stores it in a dynamic array
    // returns the pointer to the dynamic array
    FILE *source = fopen("/Users/vulcanwm/CLionProjects/memoryexplorer/data.txt", "r");
    if (source == NULL) {
        printf("source not found");
        return;
    }
    char line[100];

    while (fgets(line, 100, source)) {
        char username[50];
        int score;
        sscanf(line, "%49[^,],%d", username, &score);
        int bucket = ht_get_bucket(username);
        ht_leaderboard *ptr = table[bucket];

        ht_leaderboard *newPtr = malloc(sizeof(ht_leaderboard));
        if (newPtr == NULL) {
            printf("memory allocation failed");
            return;
        }
        strcpy(newPtr->username, username);
        newPtr->score = score;
        newPtr->next = ptr;
        table[bucket] = newPtr;
    }

    fclose(source);
}

void ht_unload(ht_leaderboard *table[26]) {
    // frees all the memory used in the hash table
    for (int i = 0; i < 26; i++) {
        ht_leaderboard *ptr = table[i];
        while (ptr != NULL) {
            ht_leaderboard *newPtr = ptr->next;
            free(ptr);
            ptr = newPtr;
        }
    }
}

void ht_add_data(ht_leaderboard *table[26], const char *username, int score) {
    // adds a data entry to the hash table
    int bucket = ht_get_bucket(username);
    ht_leaderboard *ptr = table[bucket];
    ht_leaderboard *newPtr = malloc(sizeof(ht_leaderboard));
    if (newPtr == NULL) {
        printf("memory allocation failed");
        return;
    }
    newPtr->score = score;
    strcpy(newPtr->username, username);
    newPtr->next = ptr;
    table[bucket] = newPtr;
}

void ht_display(ht_leaderboard *table[26]) {
    // displays all the data contained in the hash table
    for (int i = 0; i < 26; i++) {
        ht_leaderboard *ptr = table[i];
        while (ptr != NULL) {
            printf("username: %s, score: %d\n", ptr->username, ptr->score);
            ptr = ptr->next;
        }
    }
}

int ht_search_data(ht_leaderboard *table[26], const char *username) {
    // searches for a data entry with the username given in the parameter
    // returns the score or -1 if not found
    int bucket = ht_get_bucket(username);
    ht_leaderboard *ptr = table[bucket];
    while (ptr != NULL) {
        if (strcmp(ptr->username, username) == 0) {
            return ptr->score;
        }
        ptr = ptr->next;
    }
    return -1;
}

void ht_amend_data(ht_leaderboard *table[26], const char *username, int score) {
    // amends a data entry in the hash table
    int bucket = ht_get_bucket(username);
    ht_leaderboard *ptr = table[bucket];
    while (ptr != NULL) {
        if (strcmp(ptr->username, username) == 0) {
            ptr->score = score;
            return;
        }
        ptr = ptr->next;
    }
}

void ht_remove_data(ht_leaderboard *table[26], const char *username) {
    // removes a data entry in the hash table
    int bucket = ht_get_bucket(username);
    ht_leaderboard *ptr = table[bucket];
    if (ptr == NULL) return;
    if (strcmp(ptr->username, username) == 0) {
        table[bucket] = ptr->next;
        free(ptr);
        return;
    }
    while (ptr->next != NULL) {
        if (strcmp(ptr->next->username, username) == 0) {
            ht_leaderboard *newPtr = ptr->next->next;
            free(ptr->next);
            ptr->next = newPtr;
            break;
        }
        ptr = ptr->next;
    }
}