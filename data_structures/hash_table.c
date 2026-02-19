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
void remove_data(leaderboard *table[26], const char *username);
void amend_data(leaderboard *table[26], const char *username, int score);
void display(leaderboard *table[26]);
int search_data(leaderboard *table[26], const char *username);

int main() {
    leaderboard *table[26];
    for (int i = 0; i < 26; i++) {
        table[i] = NULL;
    }

    load(table);
    printf("loaded all the data\n");
    int hi_score = search_data(table, "hi");
    printf("hi's score: %d\n", hi_score);
    amend_data(table, "hi", 123456);
    printf("changed hi's score to 123456\n");
    remove_data(table, "abcde");
    printf("removed user abcde\n");
    add_data(table, "new user", 1000);
    printf("added new user\n");
    printf("displaying the data\n");
    display(table);
    unload(table);
    printf("unloaded all the data\n");
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

void display(leaderboard *table[26]) {
    for (int i = 0; i < 26; i++) {
        leaderboard *ptr = table[i];
        while (ptr != NULL) {
            printf("username: %s, score: %d\n", ptr->username, ptr->score);
            ptr = ptr->next;
        }
    }
}

int search_data(leaderboard *table[26], const char *username) {
    for (int i = 0; i < 26; i++) {
        leaderboard *ptr = table[i];
        while (ptr != NULL) {
            if (strcmp(ptr->username, username) == 0) {
                return ptr->score;
            }
            ptr = ptr->next;
        }
    }
    return -1;
}

void amend_data(leaderboard *table[26], const char *username, int score) {
    for (int i = 0; i < 26; i++) {
        leaderboard *ptr = table[i];
        while (ptr != NULL) {
            if (strcmp(ptr->username, username) == 0) {
                ptr->score = score;
                return;
            }
            ptr = ptr->next;
        }
    }
}

void remove_data(leaderboard *table[26], const char *username) {
    for (int i = 0; i < 26; i++) {
        leaderboard *ptr = table[i];
        if (strcmp(ptr->username, username) == 0) {
            table[i] = ptr->next;
            free(ptr);
            return;
        }
        while (ptr->next != NULL) {
            if (strcmp(ptr->next->username, username) == 0) {
                leaderboard *newPtr = ptr->next->next;
                free(ptr->next);
                ptr->next = newPtr;
                break;
            }
            ptr = ptr->next;
        }
    }
}