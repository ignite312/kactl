/**
 * Author: Tspectre
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
#pragma once

struct FenwickTree {
    // 0 base indexing
    vector<int> bit;
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }
    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
