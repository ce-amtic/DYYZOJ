#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int CN = 5e4 + 10, P = 998244353;
int read() {
    int s = 0, ne = 1; char c = getchar();
    for(; c < '0' || c > '9'; c = getchar()) if(c == '-') ne = -1;
    for(; c >= '0' && c <= '9'; c = getchar()) s = (s << 1) + (s << 3) + c - '0';
    return s * ne;
}
int iv[CN << 2] = {0, 1};
void init(int n) {
    for(int i = 2; i <= n; i++) iv[i] = 1ll * iv[P % i] * (P - P / i) % P;
}
int add(int x, int y) {
    return x + y >= P ? x + y - P : x + y;
}
int qp(int a, int b) {
    int r = 1;
    for(; b; b >>= 1, a = 1ll * a * a % P) if(b & 1) r = 1ll * r * a % P;
    return r;
}
int rev[CN << 2];
void cg(int t[], int n) {
    for(int i = 0; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + (i & 1) * (n >> 1);
    for(int i = 0; i < n; i++) if(i < rev[i]) swap(t[i], t[rev[i]]);
}
void ntt(int t[], int n, int tp) {
    int G = 3, iG = qp(G, P - 2); cg(t, n);
    for(int w = 2; w <= n; w <<= 1) {
        int l = w >> 1, gn = qp(tp ? G : iG, (P - 1) / w);
        for(int i = 0; i < n; i += w)
            for(int j = i, g = 1; j < i + l; j++, g = 1ll * g * gn % P) {
                int u = t[j], v = 1ll * g * t[j + l] % P;
                t[j] = add(u, v), t[j + l] = add(u, P - v);
            }
    }
    if(!tp) {
        iG = qp(n, P - 2);
        for(int i = 0; i < n; i++) t[i] = 1ll * t[i] * iG % P;
    }
}
int c[CN << 2];
void inv(int a[], int b[], int n) {
    for(int i = 0; i < (n << 1); i++) c[i] = b[i] = 0; b[0] = qp(a[0], P - 2);
    for(int w = 2; w < (n << 1); w <<= 1) {
        for(int i = 0; i < w; i++) c[i] = a[i]; ntt(c, w << 1, 1), ntt(b, w << 1, 1);
        for(int i = 0; i < (w << 1); i++) b[i] = 1ll * b[i] * add(2, P - 1ll * b[i] * c[i] % P) % P;
        ntt(b, w << 1, 0); for(int i = w; i < (w << 1); i++) b[i] = 0;
    }
    for(int i = n; i < (n << 1); i++) b[i] = 0;
}
int ia[CN << 2];
void ln(int a[], int b[], int n) {
    int N = 1; while(N < (n << 1)) N <<= 1;
    for(int i = 0; i < N; i++) ia[i] = b[i] = 0; inv(a, ia, n);
    for(int i = 0; i < N; i++) c[i] = 0;
    for(int i = 0; i < n; i++) c[i] = 1ll * a[i + 1] * (i + 1) % P;
    ntt(c, N, 1), ntt(ia, N, 1);
    for(int i = 0; i < N; i++) c[i] = 1ll * c[i] * ia[i] % P;
    ntt(c, N, 0); for(int i = 1; i < n; i++) b[i] = 1ll * iv[i] * c[i - 1] % P;
}
int lnb[CN << 2];
void exp(int a[], int b[], int n) {
    for(int i = 0; i < (n << 1); i++) b[i] = lnb[i] = 0; b[0] = 1;
    for(int w = 2; w < (n << 1); w <<= 1) {
        ln(b, lnb, w); for(int i = 0; i < w; i++) lnb[i] = add(a[i], P - lnb[i]); lnb[0] = add(lnb[0], 1);
        ntt(b, w << 1, 1), ntt(lnb, w << 1, 1); for(int i = 0; i < (w << 1); i++) b[i] = 1ll * b[i] * lnb[i] % P;
        ntt(b, w << 1, 0); for(int i = w; i < (w << 1); i++) b[i] = 0;
    }
    for(int i = n; i < (n << 1); i++) b[i] = 0;
}
int n, ans = 1, A[CN << 2], B[CN << 2], s[CN << 2], tmp[CN << 2]; vector<int> res;
vector<int> solve(int l, int r) {
    if(l == r) {
        vector<int> t;
        t.pb(1), t.pb(s[l]);
        return t;
    }
    int mid = (l + r) >> 1, len, N = 1; vector<int> L = solve(l, mid), R = solve(mid + 1, r);
    len = r - l + 2; while(N < (len << 1)) N <<= 1;
    for(int i = 0; i < L.size(); i++) A[i] = L[i]; L.clear(), ntt(A, N, 1);
    for(int i = 0; i < R.size(); i++) B[i] = R[i]; R.clear(), ntt(B, N, 1);
    for(int i = 0; i < N; i++) A[i] = 1ll * A[i] * B[i] % P; ntt(A, N, 0);
    for(int i = 0; i < len; i++) L.pb(A[i]); for(int i = 0; i < N; i++) A[i] = B[i] = 0; return L;
}
int main() {
    read(), n = read(), init(n << 1); for(int i = 1; i <= n; i++) s[i] = read(), ans = 1ll * ans * s[i] % P;
    res = solve(1, n); for(int i = 0; i < n - 1; i++) tmp[i] = res[i]; ln(tmp, s, n - 1);
    for(int i = 1; i < n - 1; i++) s[i] = i & 1 ? 1ll * i * s[i] % P : P - 1ll * i * s[i] % P;
    s[0] = n; for(int i = 0; i < n - 1; i++) A[i] = i + 1; ln(A, B, n - 1);
    for(int i = 0; i < n - 1; i++) B[i] = 1ll * B[i] * s[i] % P; exp(B, A, n - 1);
    for(int i = 2; i < n - 1; i++) ans = 1ll * ans * i % P; ans = 1ll * ans * A[n - 2] % P;
    return printf("%d\n", ans), 0;
}
