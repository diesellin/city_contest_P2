#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int subtask = 0;
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--subtask" && i + 1 < argc) {
            subtask = atoi(argv[i + 1]);
        }
    }

    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readSpace();
    int Q = inf.readInt(0, 100000, "Q");
    inf.readEoln();

    if (subtask == 1) {
        ensuref(Q == 0, "Subtask 1 requires Q == 0");
    } else if (subtask == 2) {
        ensuref(Q == 0, "Subtask 2 requires Q == 0");
    } else if (subtask == 3) {
        ensuref((long long)M * Q <= 10000000LL, "Subtask 3 requires M * Q <= 10^7");
    }

    for (int i = 1; i <= M; i++) {
        /*int u =*/ inf.readInt(1, N, "u");
        inf.readSpace();
        /*int v =*/ inf.readInt(1, N, "v");
        inf.readSpace();
        int max_w = (subtask == 1 ? 1 : 100);
        /*int w =*/ inf.readInt(1, max_w, "w");
        inf.readEoln();
    }

    for (int i = 1; i <= Q; i++) {
        /*int x =*/ inf.readInt(1, N, "x");
        inf.readSpace();
        /*int d =*/ inf.readInt(0, 99, "d");
        inf.readSpace();
        /*int c =*/ inf.readInt(0, 6, "c");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
