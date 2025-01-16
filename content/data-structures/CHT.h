/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query minimum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct Line {
    // m = slope, c = intercept
    ll m, c;
    Line(ll a, ll b) : m(a), c(b) {}
};
struct CHT {
    // SayeefMahmud
    vector<Line> lines;

    bool bad(Line l1, Line l2, Line l3) {
        __int128 a = (__int128)(l2.c - l1.c) * (l2.m - l3.m);
        __int128 b = (__int128)(l3.c - l2.c) * (l1.m - l2.m);
        return a >= b;
    }
    void add(Line line) {
        lines.push_back(line);
        int sz = lines.size();
        while (sz >= 3 && bad(lines[sz - 3], lines[sz - 2], lines[sz - 1])) {
            lines.erase(lines.end() - 2);
            sz--;
        }
    }
    ll query(ll x) {
        int l = 0, r = lines.size() - 1;
        ll ans = LLONG_MAX;
        while (l <= r) {
            int mid1 = l + (r - l) / 3;
            int mid2 = r - (r - l) / 3;
            ans = min(ans, min(lines[mid1].m * x + lines[mid1].c, lines[mid2].m * x + lines[mid2].c));
            if (lines[mid1].m * x + lines[mid1].c <= lines[mid2].m * x + lines[mid2].c) {
                r = mid2 - 1;
            } else {
                l = mid1 + 1;
            }
        }
        return ans;
    }
};