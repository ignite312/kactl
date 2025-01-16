/**
 * Author: Emon
 * Description: Dijstra
 */
vector<ll> dijkstra(int s, int n, vector<vector<pair<int, ll>>> &adj) {
    vector<ll> dist(n+1, INF);
    dist[s] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, s});
    bool vis[n+1];
    memset(vis, false, sizeof(vis));
    while(!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u] = true;
        for(auto [v, wt] : adj[u]) {
            ll _d = d + wt;
            if(_d < dist[v]) {
                dist[v] = _d;
                pq.push({_d, v});
            }
        }
    }
    return dist;
}