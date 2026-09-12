#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int Q = atoi(argv[3]);
    int max_w = (argc > 4 ? atoi(argv[4]) : 100);
    string type = (argc > 5 ? string(argv[5]) : "random");

    cout << N << " " << M << " " << Q << "\n";

    vector<pair<pair<int, int>, int>> edges;

    if (type == "chain") {
        for (int i = 1; i < N && (int)edges.size() < M; i++) {
            edges.push_back({{i, i + 1}, rnd.next(1, max_w)});
        }
        while ((int)edges.size() < M) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            edges.push_back({{u, v}, rnd.next(1, max_w)});
        }
    } else if (type == "unreachable") {
        while ((int)edges.size() < M) {
            int u = rnd.next(1, max(1, N - 1));
            int v = rnd.next(1, max(1, N - 1));
            edges.push_back({{u, v}, rnd.next(1, max_w)});
        }
    } else if (type == "dag") {
        for (int i = 1; i < N && (int)edges.size() < M; i++) {
            edges.push_back({{i, i + 1}, rnd.next(1, max_w)});
        }
        while ((int)edges.size() < M) {
            int u = rnd.next(1, N - 1);
            int v = rnd.next(u + 1, N);
            edges.push_back({{u, v}, rnd.next(1, max_w)});
        }
    } else {
        int cur = 1;
        while (cur != N && (int)edges.size() < M) {
            int nxt = (cur == N - 1) ? N : rnd.next(cur + 1, N);
            edges.push_back({{cur, nxt}, rnd.next(1, max_w)});
            cur = nxt;
        }
        while ((int)edges.size() < M) {
            int u = rnd.next(1, N);
            int v = rnd.next(1, N);
            edges.push_back({{u, v}, rnd.next(1, max_w)});
        }
    }

    shuffle(edges.begin(), edges.end());
    for (auto& e : edges) {
        cout << e.first.first << " " << e.first.second << " " << e.second << "\n";
    }

    for (int i = 0; i < Q; i++) {
        int x = rnd.next(1, N);
        int d = rnd.next(0, min(max_w - 1, 99));
        int co = rnd.next(0, 6);
        cout << x << " " << d << " " << co << "\n";
    }

    return 0;
}
