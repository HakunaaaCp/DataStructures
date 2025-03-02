template<typename T>
struct FenwickTreeMin {
    vector<T> bit;
    int n;
    const T INF = numeric_limits<T>::max();

    FenwickTreeMin(int n) {
        this->n = n;
        bit.assign(n, INF);
    }

    FenwickTreeMin(const vector<T>& a) : FenwickTreeMin(a.size()) {
        for (int i = 0; i < n; i++) {
            bit[i] = min(bit[i], a[i]);
            int r = i | (i + 1);
            if (r < n) bit[r] = min(bit[r], bit[i]);
        }
    }

    T getmin(int r) {
        T ret = INF;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret = min(ret, bit[r]);
        return ret;
    }

    void update(int idx, T val) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] = min(bit[idx], val);
    }
};