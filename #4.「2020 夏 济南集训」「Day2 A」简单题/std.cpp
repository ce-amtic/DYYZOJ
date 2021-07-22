#include <bits/stdc++.h>
using namespace std;
#define MAXN 500000
#define MAXL 20
#define MOD 998244353
#define rint register int
#define ll long long
namespace FASTIO {
#define wa(e) ws(#e)
const int S = (1 << 23) + 5;
static char b[S], o[S], p[20], *H = b, *T = b, *O = o, *P;
static int r, s, c;
inline char gc() { return H == T ? T = (H = b) + fread(b, 1, S, stdin) : 0, H != T ? *H++ : -1; }
inline int rf() {
    s = 0;
    for (; !isdigit(c = gc()); s = c)
        ;
    for (r = c ^ 48; isdigit(c = gc()); (r *= 10) += c ^ 48)
        ;
    return s ^ 45 ? r : -r;
}
inline ll rfl() {
    ll r;
    s = 0;
    for (; !isdigit(c = gc()); s = c)
        ;
    for (r = c ^ 48; isdigit(c = gc()); (r *= 10) += c ^ 48)
        ;
    return s ^ 45 ? r : -r;
}
inline int ef() { return fwrite(o, 1, O - o, stdout), O = o, 0; }
inline int w() { return O - o > S - 128 ? ef() : 0; }
inline void wf(int x, char e = 10) {
    for (x < 0 ? *O++ = 45, x = -x : 0, x ?: *O++ = 48, P = p; x; *++P = x % 10 + 48, x /= 10)
        ;
    for (; P != p; *O++ = *P--)
        ;
    e ? *O++ = e, w() : 0;
}
inline void wfl(ll x, char e = 10) {
    for (x < 0 ? *O++ = 45, x = -x : 0, x ?: *O++ = 48, P = p; x; *++P = x % 10 + 48, x /= 10)
        ;
    for (; P != p; *O++ = *P--)
        ;
    e ? *O++ = e, w() : 0;
}
inline void ws(const char *e) {
    strcpy(O, e);
    O += strlen(e);
    w();
}
inline void wc(char e) {
    *O++ = e;
    w();
}
}  // namespace FASTIO
using FASTIO::ef;
using FASTIO::rf;
using FASTIO::rfl;
using FASTIO::wc;
using FASTIO::wf;
using FASTIO::wfl;
using FASTIO::ws;
inline int fxp(int s, int n = MOD - 2) {
    int a = 1;
    for (; n; n & 1 ? a = 1ll * a * s % MOD : 0, s = 1ll * s * s % MOD, n >>= 1)
        ;
    return a;
}
int R, K, Q, L, l, r, k, fac[MAXL], efac[MAXL], t[MAXL][MAXL], F[MAXL][MAXN + 5];
inline void Partial(int A[]) {
    for (rint i = 1; i <= R; (A[i] += A[i - 1]) < MOD ?: A[i] -= MOD, i++)
        ;
}
inline void Conv(int A[], int B[], int C[]) {
    for (rint i = 1, j, k; i <= R; i++)
        for (j = i, k = 1; j <= R; C[j] = (C[j] + 1ll * A[i] * B[k]) % MOD, j += i, k++)
            ;
}
inline int Lagrange(int k) {
    k < MOD ?: k -= MOD;
    if (k <= L)
        return (F[k][r] - F[k][l - 1]) < 0 ? F[k][r] - F[k][l - 1] + MOD : F[k][r] - F[k][l - 1];
    static int y[MAXL], lx[MAXL], rx[MAXL];
    int w = 0, z = ilogb(r) + 1;
    for (rint j = z; j; (y[j] = F[j][r] - F[j][l - 1]) < 0 ? y[j] += MOD : 0, j--)
        ;
    lx[0] = 1;
    for (int j = 1; j <= z; lx[j] = 1ll * lx[j - 1] * (k - j) % MOD, j++)
        ;
    rx[z + 1] = 1;
    for (int j = z; j; rx[j] = 1ll * rx[j + 1] * (k - j) % MOD, j--)
        ;
    for (int j = z; j; j--)
        w = (w + 1ll * ((z ^ j) & 1 ? MOD - y[j] : y[j]) * lx[j - 1] % MOD * rx[j + 1] % MOD * t[z][j]) % MOD;
    return w;
}
int main() {
    // freopen("easy.in","r",stdin); freopen("easy.out","w",stdout);
    R = rf();
    K = rf();
    Q = rf();
    L = ilogb(R) + 1;
    F[0][1] = 1;
    fill(F[1] + 1, F[1] + R + 1, 1);
    for (int j = fac[0] = efac[0] = 1; j <= L;
         fac[j] = 1ll * fac[j - 1] * j % MOD, efac[j] = fxp(fac[j]), j++)
        ;
    for (int z = 1; z <= L; z++)
        for (int j = 1; j <= z; t[z][j] = 1ll * efac[j - 1] * efac[z - j] % MOD, j++)
            ;
    for (int j = 1; j < L; Conv(F[j], F[1], F[j + 1]), j++)
        ;
    for (int j = L; j; Partial(F[j--]))
        ;
    for (; Q--; l = rf(), r = rf(), k = rf(), wf(Lagrange(k)))
        ;
    return ef();
}
