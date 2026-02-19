#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct leaderboard {
    char username[50];
    int score;
    struct leaderboard *next;
} leaderboard;

int ht_get_bucket(const char *username);
void ht_load(leaderboard *table[26]);
void ht_unload(leaderboard *table[26]);
void ht_add_data(leaderboard *table[26], const char *username, int score);
void ht_remove_data(leaderboard *table[26], const char *username);
void ht_amend_data(leaderboard *table[26], const char *username, int score);
void ht_display(leaderboard *table[26]);
int ht_search_data(leaderboard *table[26], const char *username);

#endif //HASH_TABLE_H