#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct ll_leaderboard {
    char username[50];
    int score;
    struct ll_leaderboard *next;
} ll_leaderboard;

ll_leaderboard *ll_load();
void ll_unload(ll_leaderboard *users);
ll_leaderboard *ll_add_data(ll_leaderboard *users, const char *username, int score);
ll_leaderboard *ll_remove_data(ll_leaderboard *users, const char *username);
void ll_amend_data(ll_leaderboard *users, const char *username, int score);
void ll_display(ll_leaderboard *users);
int ll_search_data(const ll_leaderboard *users, const char *username);

#endif //LINKED_LIST_H