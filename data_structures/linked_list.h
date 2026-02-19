#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct leaderboard {
    char username[50];
    int score;
    struct leaderboard *next;
} leaderboard;

leaderboard *ll_load();
void ll_unload(leaderboard *users);
leaderboard *ll_add_data(leaderboard *users, const char *username, int score);
leaderboard *ll_remove_data(leaderboard *users, const char *username);
void ll_amend_data(leaderboard *users, const char *username, int score);
void ll_display(leaderboard *users);
int ll_search_data(const leaderboard *users, const char *username);

#endif //LINKED_LIST_H