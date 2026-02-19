#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct {
    char username[50];
    int score;
} leaderboard;

leaderboard *da_load(int *size);
void da_unload(leaderboard *ptr);
leaderboard *da_add_data(leaderboard *ptr, int *size, const char *username, int score);
leaderboard *da_remove_data(leaderboard *ptr, int *size, const char *username);
void da_amend_data(leaderboard *ptr, int size, const char *username, int score);
void da_display(leaderboard *ptr, int size);
int da_search_data(const leaderboard *ptr, int size, const char *username);

#endif //DYNAMIC_ARRAY_H