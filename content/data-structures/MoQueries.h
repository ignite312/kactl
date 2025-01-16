/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source: https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate TSP through the queries,
 * and moving from one query to the next by adding/removing points at the ends.
 * If values are on tree edges, change \texttt{step} to add/remove the edge $(a, c)$ and remove the initial \texttt{add} call (but keep \texttt{in}).
 * Time: O(N \sqrt Q)
 * Status: stress-tested
 */
#pragma once

// 0-base indexing
void add(int x) {
    if(!freq[x]) distinct++;
    freq[x]++;
}
void remove(int x) {
    freq[x]--;
    if(!freq[x]) distinct--;
}
void adjust(int &curr_l, int &curr_r, int L, int R) {
    while(curr_l > L) {
        curr_l--;
        add(a[curr_l]);
    }
    while(curr_r < R) {
        curr_r++;
        add(a[curr_r]);
    }
    while(curr_l < L) {
        remove(a[curr_l]);
        curr_l++;
    }
    while(curr_r > R) {
        remove(a[curr_r]);
        curr_r--;
    }
}
void solve(vector<array<int, 3>> &queries) {
    // const int BLOCK_SIZE = sqrt(queries.size()) + 1;
    const int BLOCK_SIZE = 555;
    sort(queries.begin(), queries.end(), [&](const array<int, 3>& a, const array<int, 3>& b) {
        int blockA = a[0] / BLOCK_SIZE;
        int blockB = b[0] / BLOCK_SIZE;
        if (blockA != blockB)
            return blockA < blockB;
        return a[1] < b[1];
    });
    auto[L, R, id] = queries[0];
    int curr_l = L, curr_r = L;
    distinct = 1;
    freq[a[curr_l]]++;
    vector<int> ans(queries.size());
    for(auto [L, R, id] : queries) {
        adjust(curr_l, curr_r, L, R);
        ans[id] = distinct;
    }
    for(auto x : ans) cout << x << "\n";
}
