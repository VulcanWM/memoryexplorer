#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    int score;
} leaderboard;

leaderboard *load(int *size);
void unload(leaderboard *ptr);
leaderboard *add_data(leaderboard *ptr, int *size, const char *username, int score);
leaderboard *remove_data(leaderboard *ptr, int *size, const char *username);
void amend_data(leaderboard *ptr, int size, const char *username, int score);
void display(leaderboard *ptr, int size);
int search_data(const leaderboard *ptr, int size, const char *username);
void sort_data(); // sort all the score data based on score

int main() {
    int size = 0;
    leaderboard *users = load(&size);
    if (users == NULL)
    {
        printf("loading failed\n");
        return 1;
    }
    printf("loaded everything\n");

    printf("displaying data:\n");
    display(users, size);

    users = remove_data(users, &size, "hello");
    printf("removed user 'hello'\n");

    users = add_data(users, &size, "new user", 1000);
    printf("added user 'new user'\n");

    printf("displaying users with added data:\n");
    display(users, size);

    amend_data(users, size, "hi", 2000);
    int hiScore = search_data(users, size, "hi");
    printf("hi's score is %d\n", hiScore);

    unload(users);
    printf("unloaded everything\n");

    return 0;
}

leaderboard *load(int *size) {
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


        if (ptr == NULL) {
            ptr = malloc(sizeof(leaderboard) * (*size + 1));
            if (ptr == NULL) {
                printf("memory allocation failed");
                fclose(source);
                return NULL;
            }
        } else {
            leaderboard *temp = realloc(ptr, sizeof(leaderboard) * (*size + 1));
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

void unload(leaderboard *ptr) {
    // frees the dynamic array memory
    free(ptr);
}

void display(leaderboard *ptr, const int size) {
    // displays all the entries in the dynamic array
    for (int i = 0; i < size; i++) {
        printf("username: %s, score: %d\n", ptr[i].username, ptr[i].score);
    }
}

leaderboard *add_data(leaderboard *ptr, int *size, const char *username, const int score) {
    // adds a data entry to the dynamic array
    // returns the new pointer of the dynamic array
    leaderboard *temp = realloc(ptr, sizeof(leaderboard) * (*size + 1));
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

int search_data(const leaderboard *ptr, const int size, const char *username) {
    // searches for the score of the user with the username given as a parameter
    // returns -1 if the user has not been found
    for (int i = 0; i < size; i++){
        if (strcmp(ptr[i].username, username) == 0) {
            return ptr[i].score;
        }
    }
    return -1;
}

void amend_data(leaderboard *ptr, const int size, const char *username, int score) {
    // amends the score of a user in the dynamic array
    for (int i = 0; i < size; i++) {
        if (strcmp(ptr[i].username, username) == 0) {
            ptr[i].score = score;
            return;
        }
    }
}

leaderboard *remove_data(leaderboard *ptr, int *size, const char *username) {
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