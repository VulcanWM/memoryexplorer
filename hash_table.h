#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct ht_leaderboard {
    char username[50];
    int score;
    struct ht_leaderboard *next;
} ht_leaderboard;

int ht_get_bucket(const char *username);
void ht_load(ht_leaderboard *table[26]);
void ht_unload(ht_leaderboard *table[26]);
void ht_add_data(ht_leaderboard *table[26], const char *username, int score);
void ht_remove_data(ht_leaderboard *table[26], const char *username);
void ht_amend_data(ht_leaderboard *table[26], const char *username, int score);
void ht_display(ht_leaderboard *table[26]);
int ht_search_data(ht_leaderboard *table[26], const char *username);

#endif //HASH_TABLE_H