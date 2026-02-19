#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct leaderboard {
    char username[50];
    int score;
    struct leaderboard *next;
} leaderboard;

int get_bucket(const char *username);
void load(leaderboard *table[26]);
void unload(leaderboard *table[26]);
void add_data(leaderboard *table[26], const char *username, int score);
void remove_data();
void amend_data();
void display();
void search_data();

int hash_table() {
    leaderboard *table[26];
    for (int i = 0; i < 26; i++) {
        table[i] = NULL;
    }

    load(table);
    printf("loaded everything");
    add_data(table, "new user", 1000);
    printf("added new user\n");
    unload(table);
    printf("unloaded everything");
    return 0;
}

int get_bucket(const char *username) {
    // get the bucket of the hash table from the first letter of the username
    return tolower(username[0]) - 'a';
}

void load(leaderboard *table[26]) {
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
        int bucket = get_bucket(username);
        leaderboard *ptr = table[bucket];

        leaderboard *newPtr = malloc(sizeof(leaderboard));
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

void unload(leaderboard *table[26]) {
    // frees all the memory used in the hash table
    for (int i = 0; i < 26; i++) {
        leaderboard *ptr = table[i];
        while (ptr != NULL) {
            leaderboard *newPtr = ptr->next;
            free(ptr);
            ptr = newPtr;
        }
    }
}

void add_data(leaderboard *table[26], const char *username, int score) {
    int bucket = get_bucket(username);
    leaderboard *ptr = table[bucket];
    leaderboard *newPtr = malloc(sizeof(leaderboard));
    if (newPtr == NULL) {
        printf("memory allocation failed");
        return;
    }
    newPtr->score = score;
    strcpy(newPtr->username, username);
    newPtr->next = ptr;
    table[bucket] = newPtr;
}