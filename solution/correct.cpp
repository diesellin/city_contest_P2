#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXW = 105;
const int MAX_NODES = 115000;

int N, M, Q;
vector<int> e[MAX_NODES];
int id[MAXN][MAXW];
int c[MAX_NODES];
bool hg[128][MAX_NODES];

struct State {
    int dis;
    int mask;
    int p;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (!(cin >> N >> M >> Q)) return 0;
    
    int mxid = N;
    for (int i = 1; i <= N; i++) {
        id[i][0] = i;
        for (int j = 1; j < 102; j++) {
            id[i][j] = ++mxid;
            e[id[i][j - 1]].push_back(id[i][j]);
        }
    }
    
    while (M--) {
        int a, b, w;
        cin >> a >> b >> w;
        e[id[a][w - 1]].push_back(b);
    }
    
    while (Q--) {
        int a, d, co;
        cin >> a >> d >> co;
        if (a >= 1 && a <= N && d >= 0 && d < 102) {
            c[id[a][d]] |= (1 << co);
        }
    }

    queue<State> q;
    q.push({0, c[1], 1});
    hg[c[1]][1] = true;

    int ans = 2e9, cnt = 0;
    while (!q.empty()) {
        State cur = q.front();
        q.pop();
        int dis = cur.dis, mask = cur.mask, x = cur.p;

        if (dis > ans) continue;

        if (x == N) {
            if (dis < ans) {
                ans = dis;
                cnt = 0;
            }
            if (dis == ans) {
                int ccnt = 0;
                for (int i = 0; i < 7; i++) {
                    if (mask & (1 << i)) {
                        ccnt++;
                    }
                }
                cnt = max(cnt, ccnt);
            }
        }

        for (int y : e[x]) {
            int nmask = mask | c[y];
            if (!hg[nmask][y]) {
                hg[nmask][y] = true;
                q.push({dis + 1, nmask, y});
            }
        }
    }

    if (ans == 2e9) {
        cout << "-1 -1\n";
    } else {
        cout << ans << " " << cnt << "\n";
    }
    return 0;
}
