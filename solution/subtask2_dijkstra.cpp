#include <bits/stdc++.h>
using namespace std;

// Solves Subtask 2: Q = 0 using standard Dijkstra
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return 0;

    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }
    for (int i = 0; i < Q; i++) {
        int x, d, c;
        cin >> x >> d >> c;
    }

    vector<int> dist(N + 1, 2e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        int d = cur.first, u = cur.second;
        if (d > dist[u]) continue;
        if (u == N) break;

        for (auto& edge : adj[u]) {
            int v = edge.first, w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[N] >= 2e9) {
        cout << "-1 -1\n";
    } else {
        cout << dist[N] << " 0\n";
    }
    return 0;
}
