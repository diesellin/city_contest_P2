#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "testlib.h"
using namespace std;

// gen2: 结构化边界/压力测试生成器
//   gen2 <type> <p1> <p2> <p3> <p4> [seed-tag]
//
//   layered : p1=层数L, p2=每层宽度W, p3=每点向下一层的出度K, p4=随机标记数Qm
//             N = L*W+2，所有边权为 1（大量并列最短路，各路径收集到的标记集合不同）。
//             另外固定追加一个 (N,0,c) 标记，用来检验“到达终点时 (N,0) 的标记计入答案”。
//   diamond : p1=级数, p2=随机标记数Qm
//             每级两条等长(100)路线：直接边(w=100) 或 经中点两段(50+50)。
//             最短路条数为 2^级数。直接边可由 (s,d>=50,c) 单独标记，中点路线可由 (m,d<50,c) 标记。
//   worst   : p1=N
//             N 不可达，每级两条平行边(w=99 无标记 / w=100 带颜色)，使 BFS 展开全部 (点,集合) 状态。
//   chain100: p1=N, p2=平行边重数k, p3=随机标记数Qm
//             链上每条边都是 w=100 的 k 重边，最短路长度 100*(N-1)。
struct E { int u, v, w; };
struct O { int x, d, c; };

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string type = argv[1];
    int p1 = atoi(argv[2]);
    int p2 = atoi(argv[3]);
    int p3 = atoi(argv[4]);
    int p4 = atoi(argv[5]);

    int N = 0;
    vector<E> es;
    vector<O> os;

    if (type == "layered") {
        int L = p1, W = p2, K = min(p3, p2), Qm = p4;
        N = L * W + 2;
        auto id = [&](int l, int i) { return 2 + l * W + i; };
        for (int i = 0; i < W; i++) es.push_back({1, id(0, i), 1});
        for (int l = 0; l + 1 < L; l++) {
            for (int i = 0; i < W; i++) {
                vector<int> p = rnd.perm(W);
                for (int t = 0; t < K; t++) es.push_back({id(l, i), id(l + 1, p[t]), 1});
            }
        }
        for (int i = 0; i < W; i++) es.push_back({id(L - 1, i), N, 1});
        for (int i = 0; i < Qm; i++) os.push_back({rnd.next(1, N), 0, rnd.next(0, 6)});
        os.push_back({N, 0, rnd.next(0, 6)});
    } else if (type == "diamond") {
        int levels = p1, Qm = p2;
        N = 2 * levels + 1;
        for (int j = 0; j < levels; j++) {
            int s = 2 * j + 1, m = 2 * j + 2, t = 2 * j + 3;
            es.push_back({s, t, 100});
            es.push_back({s, m, 50});
            es.push_back({m, t, 50});
        }
        for (int i = 0; i < Qm; i++) {
            int j = rnd.next(0, levels - 1);
            int c = rnd.next(0, 6);
            if (rnd.next(0, 1) == 0) os.push_back({2 * j + 1, rnd.next(50, 99), c});
            else os.push_back({2 * j + 2, rnd.next(0, 49), c});
        }
    } else if (type == "worst") {
        N = p1;
        for (int i = 1; i <= N - 2; i++) {
            es.push_back({i, i + 1, 99});
            es.push_back({i, i + 1, 100});
            os.push_back({i, 99, i % 7});
        }
    } else if (type == "chain100") {
        N = p1;
        int k = p2, Qm = p3;
        for (int i = 1; i < N; i++)
            for (int t = 0; t < k; t++) es.push_back({i, i + 1, 100});
        for (int i = 0; i < Qm; i++) os.push_back({rnd.next(1, N), rnd.next(0, 99), rnd.next(0, 6)});
    } else {
        quitf(_fail, "unknown type %s", type.c_str());
    }

    shuffle(es.begin(), es.end());
    shuffle(os.begin(), os.end());

    cout << N << " " << es.size() << " " << os.size() << "\n";
    for (auto& e : es) cout << e.u << " " << e.v << " " << e.w << "\n";
    for (auto& o : os) cout << o.x << " " << o.d << " " << o.c << "\n";
    return 0;
}
