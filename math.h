#include "header.h"

const int N = 2e5 + 1, M = 1e9 + 7;
int inv[N], invfact[N], fact[N];

void init() {
    inv[1] = 1;
    for(int i = 2; i < N; i++) inv[i] = M - 1LL * M / i * inv[M % i] % M; 
    fact[0] = invfact[0] = 1;
    for(int i = 1; i < N; i++) {
        invfact[i] = 1LL * invfact[i - 1] * inv[i] % M;
        fact[i] = (1LL * fact[i - 1] * i) % M;
    }
}

int C(int n, int m) {
    if(m > n) return 0;
    return 1LL * fact[n] * invfact[n - m] % M * invfact[m] % M; 
}

int pov(int base, int exp) {
    int ans = 1;
    while(exp) {
        if(exp & 1) ans = (1LL * ans * base) % M;
        base = (1LL * base * base) % M;
        exp >>= 1;
    }
    return ans; 
}
