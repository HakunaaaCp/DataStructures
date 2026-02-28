template<typename T>
struct Sparse {
    int n, m;
    vector<T> a;
    vector<vector<int>> dp;
    Sparse(vector<T> a) : n((int)a.size()), a(a), m(log2(n)) {
        dp.resize(n, vector<int>(m + 1));
        for(int i = 0; i < n; i++) dp[i][0] = a[i];
        for(int i = 1; i <= m; i++) {
            for(int j = 0; j < n - (1 << i) + 1; j++) {
                dp[j][i] = min(dp[j][i - 1], dp[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    T get(int l, int r) {
        int sz = log2(r - l + 1);
        return min(dp[l][sz], dp[r - (1 << sz) + 1][sz]);
    }
};