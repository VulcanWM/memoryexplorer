#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char username[50];
    int score;
} leaderboard;

int load(); // load from a text file into memory
void unload(); // unload all the memory
void add_data(); // add data to the dynamic array
void remove_data(); // remove data from the dynamic array
void amend_data(); // amend a score of a user
void display(); // display all the scores
void search_data(); // search for the score of a user
void sort_data(); // sort all the score data based on score

int main() {
    // leaderboard leader = {"user1", 50};
    // printf("%s\n", leader.username);
    // printf("%d\n", leader.score);
    // printf("%zo\n", sizeof(leaderboard));
    load();
    return 0;
}

int load() {
    FILE *source = fopen("/Users/vulcanwm/CLionProjects/memoryexplorer/data.txt", "r");
    if (source == NULL) {
        printf("source not found");
        return 1;
    }
    char line[100];
    leaderboard *ptr = NULL;
    int size = 0;

    while (fgets(line, 100, source)) {
        size++;
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
        printf("username: %s\n", username);
        printf("score: %i\n", score);

        if (ptr == NULL) {
            ptr = malloc(sizeof(leaderboard) * size);
            if (ptr == NULL) {
                printf("memory allocation failed");
                size--;
                return 1;
            }
        } else {
            leaderboard *temp = realloc(ptr, sizeof(leaderboard) * size);
            if (temp == NULL)
            {
                printf("memory allocation failed");
                size--;
                return 1;
            }
            ptr = temp;
        }
        ptr[size-1].score = score;
        strcpy(ptr[size-1].username, username);
    }

    fclose(source);
    return 0;
}