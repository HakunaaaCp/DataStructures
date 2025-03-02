template <typename T>
struct FenwickTree {
    std::vector<T> bit;
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, T());
    }

    FenwickTree(const std::vector<T>& a) : FenwickTree(a.size()) {
        for(int i = 0; i < n; i++) {
            bit[i] += a[i];
            int r = i | (i + 1);
            if (r < n) bit[r] += bit[i];
        }
    }

    T sum(int r) {
        T ret = T();
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, T delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};