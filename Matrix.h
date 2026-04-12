#include <bits/stdc++.h>
using namespace std;

struct Mat {
    int n;
    vector<int> d;

    Mat(int n, int val = 0) : n(n), d(n * n, val) {}

    int& operator()(int i, int j)       { return d[i * n + j]; }
    int  operator()(int i, int j) const { return d[i * n + j]; }

    Mat(const Mat& other) : n(other.n), d(other.d) {}

    Mat& operator=(const Mat& other) {
        assert(n == other.n);
        d = other.d;
        return *this;
    }

    Mat operator*(const Mat& other) const {
        assert(n == other.n);
        Mat ans(n, 0);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if ((*this)(i, k) == 0) continue;
                for (int j = 0; j < n; j++) {
                    ans(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return ans;
    }

    Mat& operator*=(const Mat& other) {
        *this = *this * other;
        return *this;
    }
};