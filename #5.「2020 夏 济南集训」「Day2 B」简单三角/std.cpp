#include <bits/stdc++.h>
using namespace std;
#define MAXN 400000
#define MOD 998244353
#define INV2 499122177
#define X first
#define Y second
#define pii pair<int, int>
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
inline int GCD(int a, int b) { return b ? GCD(b, a % b) : a; }
inline long long dis(const pii &A, const pii &B) {
    return 1ll * (A.X - B.X) * (A.X - B.X) + 1ll * (A.Y - B.Y) * (A.Y - B.Y);
}
map<pii, int> S;
pii P[MAXN + 5];
long long l[MAXN + 5];
vector<int> e[MAXN + 5];
bool R[MAXN + 5];
int n, m, r, d[MAXN + 5], u[MAXN + 5], v[MAXN + 5], c[MAXN + 5], b[MAXN + 5], g[MAXN + 5];
inline int Add(int x, int y) {
    pii _ = make_pair(x, y);
    if (S.count(_))
        return S[_];
    P[S[_] = ++n] = _;
    return n;
}
inline bool Judge(int e1, int e2, int e3) {
    long long c = max(max(l[e1], l[e2]), l[e3]), a = min(min(l[e1], l[e2]), l[e3]);
    return a + (l[e1] ^ l[e2] ^ l[e3] ^ a ^ c) > c;
}
inline int Simp(int e1, int e2, int e3) {
    int x[3] = { P[u[e3]].X, P[v[e1]].X, P[v[e2]].X }, y[3] = { P[u[e3]].Y, P[v[e1]].Y, P[v[e2]].Y };
    int S = MOD - (1ll * abs(x[0] - x[1]) * abs(y[0] - y[1]) + 1ll * abs(x[0] - x[2]) * abs(y[0] - y[2]) +
                   1ll * abs(x[1] - x[2]) * abs(y[1] - y[2])) %
                      MOD;
    sort(x, x + 3);
    sort(y, y + 3);
    return ((S + 2 + 2ll * (y[2] - y[0]) * (x[2] - x[0]) - g[e1] - g[e2] - g[e3]) % MOD + MOD) * c[e1] % MOD *
           c[e2] % MOD * c[e3] % MOD;
}
int main() {
    // freopen("triangle.in","r",stdin); freopen("triangle.out","w",stdout);
    m = rf();
    for (rint i = 1, x, y; i <= m;
         x = rf(), y = rf(), ++d[u[i] = Add(x, y)], x = rf(), y = rf(), ++d[v[i] = Add(x, y)], i++)
        ;
    S.clear();
    for (rint i = 1; i <= m;
         (d[u[i]] ^ d[v[i]] ? d[u[i]] < d[v[i]] : u[i] < v[i]) ?: u[i] ^= v[i] ^= u[i] ^= v[i],
              R[i] = S[pii(u[i], v[i])]++, i++)
        ;
    for (rint i = m; i; c[i] = S[pii(u[i], v[i])], !R[i] ? e[u[i]].push_back(i), l[i] = dis(P[u[i]], P[v[i]]),
              g[i] = GCD(abs(P[u[i]].X - P[v[i]].X), abs(P[u[i]].Y - P[v[i]].Y)) : 0, i--)
        ;
    S.clear();
    for (rint i = 1; i <= n; i++) {
        for (int e3 : e[i]) b[v[e3]] = e3;
        for (int e1 : e[i])
            for (int e2 : e[v[e1]])
                r = (r + (b[v[e2]] && Judge(e1, e2, b[v[e2]]) ? Simp(e1, e2, b[v[e2]]) : 0)) % MOD;
        for (int e3 : e[i]) b[v[e3]] = 0;
    }
    return wf(1ll * r * INV2 % MOD), ef();
}
