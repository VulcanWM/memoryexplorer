#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dynamic_array.h"
#include "linked_list.h"
#include "hash_table.h"

#define DATA_FILE "data.txt"

int main() {
    clock_t start, end;
    double elapsed;

    int da_size = 0;
    da_leaderboard *da = NULL;

    ll_leaderboard *ll = NULL;

    ht_leaderboard *ht[26] = {NULL};

    // ------------ DYNAMIC ARRAY LOAD ------------
    start = clock();
    da = da_load(&da_size);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[DA] Load %d entries: %f seconds\n", da_size, elapsed);

    // ------------ LINKED LIST LOAD ------------
    start = clock();
    ll = ll_load();
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[LL] Load: %f seconds\n", elapsed);

    // ------------ HASH TABLE LOAD ------------
    start = clock();
    ht_load(ht);
    end = clock();
    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("[HT] Load: %f seconds\n", elapsed);

    // ------------ SEARCH BENCHMARK ------------
    const char *test_user = "quebec10";

    start = clock();
    int score_da = da_search_data(da, da_size, test_user);
    end = clock();
    printf("[DA] Search %s: score=%d, time=%f\n", test_user, score_da, (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    int score_ll = ll_search_data(ll, test_user);
    end = clock();
    printf("[LL] Search %s: score=%d, time=%f\n", test_user, score_ll, (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    int score_ht = ht_search_data(ht, test_user);
    end = clock();
    printf("[HT] Search %s: score=%d, time=%f\n", test_user, score_ht, (double)(end - start) / CLOCKS_PER_SEC);

    // ------------ ADD BENCHMARK ------------
    start = clock();
    da = da_add_data(da, &da_size, "benchmark_user", 9999);
    end = clock();
    printf("[DA] Add: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    ll = ll_add_data(ll, "benchmark_user", 9999);
    end = clock();
    printf("[LL] Add: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    ht_add_data(ht, "benchmark_user", 9999);
    end = clock();
    printf("[HT] Add: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ------------ AMEND BENCHMARK ------------
    start = clock();
    da_amend_data(da, da_size, "benchmark_user", 12345);
    end = clock();
    printf("[DA] Amend: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    ll_amend_data(ll, "benchmark_user", 12345);
    end = clock();
    printf("[LL] Amend: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    ht_amend_data(ht, "benchmark_user", 12345);
    end = clock();
    printf("[HT] Amend: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ------------ REMOVE BENCHMARK ------------
    start = clock();
    da = da_remove_data(da, &da_size, "benchmark_user");
    end = clock();
    printf("[DA] Remove: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    ll = ll_remove_data(ll, "benchmark_user");
    end = clock();
    printf("[LL] Remove: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    ht_remove_data(ht, "benchmark_user");
    end = clock();
    printf("[HT] Remove: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

    // ------------ CLEANUP ------------
    da_unload(da);
    ll_unload(ll);
    ht_unload(ht);

    return 0;
}