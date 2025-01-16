/**
 * Author: Simon Lindholm
 * Date: 2015-02-23
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Bellman-Ford_algorithm
 * Description: Calculates shortest paths from $s$ in a graph that might have negative edge weights.
 * Unreachable nodes get dist = inf; nodes reachable through negative-weight cycles get dist = -inf.
 * Assumes $V^2 \max |w_i| < \tilde{} 2^{63}$.
 * Time: O(VE)
 * Status: Tested on kattis:shortestpath3
 */
#pragma once

void BellmanFord(int st, int n) {
    vector<ll> dist(n+1, INF);
    vector<int> parent(n+1, -1);
    dist[st] = 0;
    for (int i = 0; i < n-1; i++) {
        bool any = false;
        for (auto[u, v, cost] : edges)
            if (dist[u] < INF)
                if (dist[v] > dist[u] + cost) {
                    dist[v] = dist[u] + cost;
                    parent[v] = u;
                    any = true;
                }
        if (!any)
            break;
    }
    if (dist[n] == INF)
        cout << "-1\n";
    else {
        vector<int> path;
        for (int cur = n; cur != -1; cur = parent[cur])
            path.push_back(cur);
        reverse(path.begin(), path.end());
        for (int u : path)
            cout << u << ' ';
    }
}

void BellmanFord(int s, int n) {
    vector<ll> dist(n+1, 0);// No need to init INF here because there can be a negative cycle where you can't reach from node 1
                        // and the Graph is not necessarily connected
                        // Our concern is about to find negetive cycle not shortest distance
    vector<int> parent(n+1, -1);
    dist[s] = 0;
    int flag;
    for (int i = 0; i < n; i++) {
        flag = -1;
        for (auto[u, v, cost] : edges) {
            if (dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    parent[v] = u;
                    flag = v;
            }
        }
    }
    if (flag == -1)
        cout << "NO\n";
    else {
        int y = flag;
        for (int i = 0; i < n; ++i)
            y = parent[y];
 
        vector<int> path;
        for (int cur = y;; cur = parent[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());
        cout << "YES\n";
        for (int u : path)
            cout << u << ' ';
    }
}
