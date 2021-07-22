#include <bits/stdc++.h>
using namespace std;
#define MAXN 524288
#define MOD 998244353
#define PHI 998244352
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
#define n(x) tt[x].n
#define l(x) tt[x].l
#define P(x, y) tt[x].P[y]
#define mid ((lef + rig) >> 1)
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
typedef vector<int> Poly;
Poly P;
struct Node {
    vector<int> P[20];
    int n, l;
} tt[MAXN + 5];
int _Rv[20][MAXN + 5], *Rv, Gw[MAXN + 5], S[MAXN + 5], A[MAXN + 5], B[MAXN + 5], l, n, q;
void RV(int Rv[], int n) {
    for (rint i = 0, l = ~-ilogb(n); i<n; Rv[i] = Rv[i >> 1]>> 1 | (i & 1) << l, i++)
        ;
}
void RV(int n) { Rv = _Rv[ilogb(n)]; }
void NTT(int R[], int n, int z) {
    int t;
    for (rint i = 0; i < n; i < Rv[i] ? swap(R[i], R[Rv[i]]), 0 : 0, i++)
        ;
    for (rint d = 0, i, j, m; (m = 1 << d) < n; d++)
        for (i = 0; i < n; i += m << 1)
            for (j = 0; j < m; j++)
                t = 1ll * R[i + j + m] * Gw[j + m] % MOD,
                (R[i + j + m] = R[i + j] - t) < 0 ? R[i + j + m] += MOD : 0,
                (R[i + j] += t) < MOD ?: R[i + j] -= MOD;
    if (z) {
        t = fxp(n);
        for (rint i = 0; i < n; R[i] = 1ll * t * R[i] % MOD, i++)
            ;
        reverse(R + 1, R + n);
    }
}
void Conv(Poly &a, Poly &b, int m) {
    int na = (int)a.size(), nb = (int)b.size(), l = na + nb - 1, n = 1;
    for (; n < l; n <<= 1)
        ;
    RV(n);
    for (rint i = 0; i < n; A[i] = i < na ? a[i] : 0, B[i] = i < nb ? b[i] : 0, i++)
        ;
    NTT(A, n, 0);
    NTT(B, n, 0);
    for (rint i = 0; i < n; A[i] = 1ll * A[i] * B[i] % MOD, i++)
        ;
    NTT(A, n, 1);
    for (rint i = l - 1; i >= m; (A[i - m] += A[i]) < MOD ?: A[i - m] -= MOD, i--)
        ;
    a.assign(A, A + min(l, m));
}
void BD(int p, int lef, int rig) {
    if (lef == rig) {
        P(p, 0) = { (MOD + 1 - S[lef]) % MOD };
        P(p, 1) = { S[lef] ? MOD - S[lef] : 0, 1 };
        n(p) = 2;
        l(p) = 1;
        return;
    }
    BD(lc(p), lef, mid);
    BD(rc(p), mid + 1, rig);
    n(p) = (n(lc(p)) << 1) - 1;
    l(p) = l(lc(p)) + 1;
    for (rint j = 0, m = 1; j < l(p); Conv(P(p, j) = P(lc(p), j), P(rc(p), j), m), m <<= 1, j++)
        ;
    Conv(P(p, l(p)) = P(lc(p), l(p) - 1), P(rc(p), l(p) - 1), 1 << l(p));
}
void QU(int p, int lef, int rig, int L, int R, int m) {
    L ^ lef || R ^ rig ? L <= mid ? QU(lc(p), lef, mid, L, min(mid, R), m), 0 : 0,
        R > mid ? QU(rc(p), mid + 1, rig, max(L, mid + 1), R, m),
        0 : 0 : (Conv(P, P(p, min(ilogb(m), l(p))), m), 0);
}
void Out(int m) {
    P.resize(max((int)P.size(), m));
    wa($);
    bool flag = false;
    for (rint i = m - 1; ~i; i--)
        if (P[i]) {
            if (flag)
                ws(" + ");
            flag = true;
            if (P[i] > 1)
                wf(P[i], 0);
            if (i) {
                wa(x);
                if (i > 9)wa(^{),wf(i,0),wa(});
                else if (i > 1)
                    wa (^), wf(i, 0);
            }
        }
    wa($\n);
}
int main() {
    //	freopen("latex.in","r",stdin); freopen("latex.out","w",stdout);
    int l = MAXN, _ = PHI / l;
    l >>= 1;
    for (rint i = 0; i < l; Gw[i + l] = fxp(3, _ * i), i++)
        ;
    for (; l--; Gw[l] = Gw[l << 1])
        ;
    for (rint i = 0; i < 19; RV(_Rv[i], 1 << i), i++)
        ;
    l = rf();
    q = rf();
    generate(S + 1, S + l + 1, rf);
    for (n = 1; n < l; n <<= 1)
        ;
    BD(1, 1, n);
    for (rint l, r, m; q--; l = rf(), r = rf(), P.assign(1, 1), QU(1, 1, n, l, r, m = rf()), Out(m))
        ;
    return ef();
}
