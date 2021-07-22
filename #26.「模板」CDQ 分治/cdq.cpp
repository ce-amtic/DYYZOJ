#include<bits/stdc++.h>
using namespace std;
#define LL long long
const int CN = 1e6 + 6;
int read(){
    int s = 0, ne = 1; char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') ne = -1; c = getchar();}
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}
int n, a[CN], b[CN], c[CN], id[CN];
bool cmpa(int i, int j) {return a[i] < a[j];}
bool cmpb(int i, int j) {return b[i] < b[j];}
class BIT {
  public: int d[CN];
    void clr() {memset(d, 0, sizeof(d));}
    void md(int p) {while(p <= n) d[p]++, p += p & (-p);}
    int qu(int p) {int r = 0; while(p) r += d[p], p -= p & (-p); return r;}
} D;
LL count(int x[]){
    LL ans = 0; D.clr();
    for(int i = 1; i <= n; i++) ans += D.qu(x[i]), D.md(x[i]);
    return ans;
}
int main()
{
    freopen("cdq.in", "r", stdin);
    freopen("cdq.ans", "w", stdout);
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read(), id[i] = i;
    for(int i = 1; i <= n; i++) b[i] = read();
    for(int i = 1; i <= n; i++) c[i] = read();
    LL ans = 0;
    sort(id + 1, id + n + 1, cmpa);
    for(int i = 1; i <= n; i++) a[i] = b[id[i]];
    ans += count(a);
    for(int i = 1; i <= n; i++) a[i] = c[id[i]];
    ans += count(a);
    sort(id + 1, id + n + 1, cmpb);
    for(int i = 1; i <= n; i++) a[i] = c[id[i]];
    ans += count(a);
    ans -= (1ll * n * (n - 1)) >> 1ll, ans >>= 1ll;
    printf("%lld", ans);
    return 0;
}
