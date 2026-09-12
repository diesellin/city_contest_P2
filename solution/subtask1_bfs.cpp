#include <bits/stdc++.h>
using namespace std;

// Solves Subtask 1: W <= 1, Q = 0 using pure unweighted BFS
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N, M, Q;
    if (!(cin >> N >> M >> Q)) return 0;

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(v);
    }
    for (int i = 0; i < Q; i++) {
        int x, d, c;
        cin >> x >> d >> c;
    }

    vector<int> dist(N + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == N) break;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    if (dist[N] == -1) {
        cout << "-1 -1\n";
    } else {
        cout << dist[N] << " 0\n";
    }
    return 0;
}
