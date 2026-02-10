#include <stdio.h>

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
    leaderboard leader = {"user1", 50};
    printf("%s\n", leader.username);
    printf("%d\n", leader.score);
    printf("%zo\n", sizeof(leaderboard));
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

    while (fgets(line, 100, source)) {
        printf("%s", line);
    }
    fclose(source);
    return 0;
}