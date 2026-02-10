#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    int score;
} leaderboard;

leaderboard *load(int *size);
void unload(leaderboard *ptr);
leaderboard *add_data(leaderboard *ptr, int *size, char username[50], int score);
void remove_data(); // remove data from the dynamic array
void amend_data(); // amend a score of a user
void display(leaderboard *ptr, int size);
int search_data(const leaderboard *ptr, int size, char username[50]);
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
    users = add_data(users, &size, "new user", 1000);
    printf("added new user\n");
    printf("displaying users with added data:\n");
    display(users, size);
    int hiScore = search_data(users, size, "hi");
    printf("hi's score is %d", hiScore);
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
        char scoreStr[50];
        int scoreData = 0;
        int scoreStartIndex = 0;
        int i = 0;
        line[strcspn(line, "\n")] = '\0';
        while (line[i] != '\0') {
            if (line[i] == ',') {
                username[i] = '\0';
                scoreData++;
                scoreStartIndex = i+1;
            } else if (scoreData == 0) {
                username[i] = line[i];
            } else {
                scoreStr[i-scoreStartIndex] = line[i];
            }
            i++;
        }
        scoreStr[i-scoreStartIndex] = '\0';
        int score = atoi(scoreStr);

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

leaderboard *add_data(leaderboard *ptr, int *size, char username[50], const int score) {
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

int search_data(const leaderboard *ptr, const int size, char username[50]) {
    // searches for the score of the user with the username given in the parameter
    // returns -1 if the user has not been found
    for (int i = 0; i < size; i++){
        if (strcmp(ptr[i].username, username) == 0) {
            return ptr[i].score;
        }
    }
    return -1;
}