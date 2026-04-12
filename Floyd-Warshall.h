#include <bits/stdc++.h>
using namespace std;

#define int long long
const int inf = LLONG_MAX / 2;

struct Mat {
    int n;
    vector<int> d;
    Mat(int n, int val) : n(n), d(n * n, val) {}
    int& operator()(int i, int j) { return d[i * n + j]; }
    int operator()(int i, int j) const { return d[i * n + j]; }
};

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    Mat M(n, inf);
    for (int i = 0; i < n; i++) M(i, i) = 0;

    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        M(a, b) = min(M(a, b), c);
        M(b, a) = min(M(b, a), c);
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) {
            if (M(i, k) == inf) continue;
            for (int j = 0; j < n; j++) {
                if (M(k, j) == inf) continue;
                M(i, j) = min(M(i, j), M(i, k) + M(k, j));
            }
        }

    while (q--) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << (M(a, b) >= inf ? -1 : M(a, b)) << '\n';
    }

    return 0;
}