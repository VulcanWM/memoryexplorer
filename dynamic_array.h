#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct {
    char username[50];
    int score;
} da_leaderboard;

da_leaderboard *da_load(int *size);
void da_unload(da_leaderboard *ptr);
da_leaderboard *da_add_data(da_leaderboard *ptr, int *size, const char *username, int score);
da_leaderboard *da_remove_data(da_leaderboard *ptr, int *size, const char *username);
void da_amend_data(da_leaderboard *ptr, int size, const char *username, int score);
void da_display(da_leaderboard *ptr, int size);
int da_search_data(const da_leaderboard *ptr, int size, const char *username);

#endif //DYNAMIC_ARRAY_H