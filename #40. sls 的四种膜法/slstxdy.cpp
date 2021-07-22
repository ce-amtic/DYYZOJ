#include<bits/stdc++.h>
using namespace std; const int CN = 2e5 + 10, P = 1004535809, i2 = (P + 1) >> 1;
int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
int qp(int a, int b) {int r = 1; for(; b; b >>= 1, a = 1ll * a * a % P) if(b & 1) r = 1ll * r * a % P; return r;}
int inv(int x) {return qp(x, P - 2);} int rev[CN << 2];
void cg(int t[], int n) {for(int i = 0; i < n; i++) rev[i] = (rev[i >> 1] >> 1) + (i & 1) * (n >> 1); for(int i = 0; i < n; i++) if(i < rev[i]) swap(t[i], t[rev[i]]);}
void ntt(int t[], int n, int tp){
    cg(t, n); int G = 3, iG = inv(G);
    for(int w = 2; w <= n; w <<= 1){
        int l = w >> 1, gn = qp(tp ? G : iG, (P - 1) / w);
        for(int i = 0; i < n; i += w) for(int j = i, g = 1; j < i + l; j++){
            int u = t[j], v = 1ll * g * t[j + l] % P; 
            t[j] = add(u, v), t[j + l] = add(u, P - v), g = 1ll * g * gn % P;
        }
    }
    if(!tp) {iG = inv(n); for(int i = 0; i < n; i++) t[i] = 1ll * t[i] * iG % P;}
}
int n, fn[CN], m, a, an, ia, ia1, sls, fac[CN], ifac[CN], T[CN], A[CN << 2], B[CN << 2];
int C(int n, int m) {return m < 0 || m > n ? 0 : 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P;}
int X(int k, int n, int a) {int res = 0, pw = 1; for(int i = 0; i <= min(k, n); i++) res = add(res, 1ll * C(k, i) * pw % P), pw = 1ll * pw * a % P; return res;}
int D(int k, int n, int a) {int res = 0, pw = qp(2, n), fail = 1; for(int j = 0; j <= k; j++) res = add(res, 1ll * A[j] * pw % P * fail % P), pw = 1ll * pw * i2 % P, fail = 1ll * fail * (n - j) % P; return res;}
int Y(int k, int n, int a) {int res = 0; for(int j = 0; j <= k; j++) res = add(res, 1ll * A[j] * fac[j] % P * T[j] % P); return res;}
int main(){
    freopen("slstxdy.in", "r", stdin), freopen("slstxdy.out", "w", stdout);
    n = 2e5, fac[0] = ifac[0] = ifac[1] = 1; for(int i = 2; i <= n; i++) ifac[i] = 1ll * ifac[P % i] * (P - P / i) % P;
    for(int i = 1; i <= n; i++) ifac[i] = 1ll * ifac[i - 1] * ifac[i] % P, fac[i] = 1ll * fac[i - 1] * i % P;
    cin >> m >> n >> a, an = qp(a, n), ia = inv(a), ia1 = inv(a - 1), fn[0] = 1;
    for(int i = 1; i <= m; i++) fn[i] = 1ll * fn[i - 1] * (n - i + 2) % P;
    T[0] = 1ll * ia1 * add(1ll * an * a % P, P - 1) % P, sls = 1ll * a * ia1 % P;
    for(int i = 1; i <= m; i++) T[i] = 1ll * sls * add(1ll * fn[i] * ifac[i] % P * an % P, P - T[i - 1]) % P;
    for(int i = 0; i <= m; i++) A[i] = (i & 1 ? P - ifac[i] : ifac[i]), B[i] = 1ll * ifac[i] * qp(i, m) % P;
    int N = 1; while(N < ((m + 1) << 1)) N <<= 1; ntt(A, N, 1), ntt(B, N, 1);
    for(int i = 0; i < N; i++) A[i] = 1ll * A[i] * B[i] % P; ntt(A, N, 0);
    return cout << T[m] << ' ' <<  X(m, n, a) << ' ' << D(m, n, a) << ' ' << Y(m, n, a) << endl, 0;
}
