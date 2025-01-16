/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Self-explanatory methods for string hashing.( Arithmetic mod $2^{64}-1$. 2x slower than mod $2^{64}$ and more code, but works on evil test data (e.g. Thue-Morse, where ABBA... and BAAB... of length $2^{10}$ hash the same mod $2^{64}$). "typedef ull H;" instead if you think test data is random, or work mod $10^{9}+7$ if the Birthday paradox is not a problem.)
 * Status: stress-tested
 */
#pragma once

struct Hashing {
    // 0-base indexing
    int n;
    FenwickTree ft1, ft2;
    Hashing() : n(0), ft1(0), ft2(0) {}
    void build_hash(string &s, int size) {
        init();
        n = size;
        ft1 = FenwickTree(n);
        ft2 = FenwickTree(n);
        for(int i = 0; i < n; i++) {
            int hash_value = p_ip1[i][0]*1LL*s[i] % M1;
            ft1.add(i, hash_value);
            hash_value = p_ip2[i][0]*1LL*s[i] % M2;
            ft2.add(i, hash_value);
        } 
    }
    void update(int i, char c) {
        int hash_value = p_ip1[i][0]*1LL*c % M1;
        ft1.add(i, (-ft1.sum(i, i) + hash_value + M1) % M1);
        hash_value = p_ip2[i][0]*1LL*c % M2;
        ft2.add(i, (-ft2.sum(i, i) + hash_value + M2) % M2);
    }
    array<int, 2> get_hash(int l, int r) {
        array<int, 2> ans;
        ans[0] = ((ft1.sum(l, r) + M1) % M1)*1LL*p_ip1[l][1] % M1;
        ans[1] = ((ft2.sum(l, r) + M2) % M2)*1LL*p_ip2[l][1] % M2;
        return ans;
    }
    array<int, 2> get_hash() {return get_hash(0, n-1);}
} h, rh;

bool check_palindrome(int i, int j, int n) {
    // 0-base indexing
    return h.get_hash(i, j) == rh.get_hash(n - j - 1, n - i - 1);
}