template<typename T>
struct FenwickTree2D {
    vector<vector<T>> bit;
    int n, m;

    void init(int n, int m) {
        this->n = n;
        this->m = m;
        bit.assign(n, vector<T>(m, 0));
    }

    void init(const vector<vector<T>>& a) {
        n = a.size();
        if (n == 0) {
            m = 0;
            bit.clear();
            return;
        }
        m = a[0].size();
        bit.assign(n, vector<T>(m, 0));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                bit[i][j] += a[i][j];
                int r1 = i | (i + 1);
                int r2 = j | (j + 1);
                if (r1 < n) bit[r1][j] += bit[i][j];
                if (r2 < m) bit[i][r2] += bit[i][j];
                if (r1 < n && r2 < m) bit[r1][r2] -= bit[i][j];
            }
        }
    }

    T sum(int x, int y) {
        T ret = 0;
        for(int i = x; i >= 0; i = (i & (i + 1)) - 1)
            for(int j = y; j >= 0; j = (j & (j + 1)) - 1)
                ret += bit[i][j];
        return ret;
    }

    void add(int x, int y, T delta) {
        for(int i = x; i < n; i = i | (i + 1))
            for(int j = y; j < m; j = j | (j + 1))
                bit[i][j] += delta;
    }
};