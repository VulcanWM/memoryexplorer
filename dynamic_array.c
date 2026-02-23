#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

da_leaderboard *da_load(int *size) {
    // loads the data from a text file and stores it in a dynamic array
    // returns the pointer to the dynamic array
    FILE *source = fopen("data.txt", "r");
    if (source == NULL) {
        printf("source not found");
        return NULL;
    }
    char line[100];
    da_leaderboard *ptr = NULL;

    while (fgets(line, 100, source)) {
        char username[50];
        int score;
        sscanf(line, "%49[^,],%d", username, &score);


        if (ptr == NULL) {
            ptr = malloc(sizeof(da_leaderboard) * (*size + 1));
            if (ptr == NULL) {
                printf("memory allocation failed");
                fclose(source);
                return NULL;
            }
        } else {
            da_leaderboard *temp = realloc(ptr, sizeof(da_leaderboard) * (*size + 1));
            if (temp == NULL) {
                printf("memory allocation failed");
                free(ptr);
                fclose(source);
                return NULL;
            }
            ptr = temp;
        }
        ptr[*size].score = score;
        strcpy(ptr[*size].username, username);
        *size += 1;
    }

    fclose(source);
    return ptr;
}

void da_unload(da_leaderboard *ptr) {
    // frees the dynamic array memory
    free(ptr);
}

void da_display(da_leaderboard *ptr, const int size) {
    // displays all the entries in the dynamic array
    for (int i = 0; i < size; i++) {
        printf("username: %s, score: %d\n", ptr[i].username, ptr[i].score);
    }
}

da_leaderboard *da_add_data(da_leaderboard *ptr, int *size, const char *username, const int score) {
    // adds a data entry to the dynamic array
    // returns the new pointer of the dynamic array
    da_leaderboard *temp = realloc(ptr, sizeof(da_leaderboard) * (*size + 1));
    if (temp == NULL) {
        printf("memory allocation failed");
        return ptr;
    }
    ptr = temp;
    strcpy(ptr[*size].username, username);
    ptr[*size].score = score;
    (*size)++;
    return ptr;
}

int da_search_data(const da_leaderboard *ptr, const int size, const char *username) {
    // searches for the score of the user with the username given as a parameter
    // returns -1 if the user has not been found
    for (int i = 0; i < size; i++){
        if (strcmp(ptr[i].username, username) == 0) {
            return ptr[i].score;
        }
    }
    return -1;
}

void da_amend_data(da_leaderboard *ptr, const int size, const char *username, int score) {
    // amends the score of a user in the dynamic array
    for (int i = 0; i < size; i++) {
        if (strcmp(ptr[i].username, username) == 0) {
            ptr[i].score = score;
            return;
        }
    }
}

da_leaderboard *da_remove_data(da_leaderboard *ptr, int *size, const char *username) {
    // deletes the data entry of the user with the username given as a parameter
    // returns the pointer to the new memory
    if (*size == 0) {
        return ptr;
    }

    int index = -1;

    for (int i = 0; i < *size; i++) {
        if (strcmp(ptr[i].username, username) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return ptr;
    }

    ptr[index] = ptr[*size-1];

    (*size)--;

    if (*size == 0) {
        free(ptr);
        return NULL;
    }
    return ptr;
}