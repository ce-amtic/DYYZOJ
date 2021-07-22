#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define il inline
#define re register
const int CN = 1e6 + 3;
const int INF = 0x3f3f3f3f;
const int P = 191011109;
const int B = 39; int ha[CN], pB[CN];
il int read(){
    re int s = 0, ne = 1; char c = getchar();
    for(;c < '0' || c > '9';c = getchar()) if(c == '-') ne = -1;
    for(;c >= '0' && c <= '9';c = getchar()) s = (s << 1) + (s << 3) + c - '0';
    return s * ne;
}
il void write(int x) {if(x > 9) write(x / 10); putchar('0' + x % 10);}
il int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
il int get(int l, int r) {return add(ha[r], P - (1ll * ha[l - 1] * pB[r - l + 1] % P));}
int n; char ch[CN];
int LCP(int l1, int r1, int l2, int r2){
    if(ch[l1] != ch[l2]) return 0;
    int l = 1, r = min(r1 - l1 + 1, r2 - l2 + 1);
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(get(l1, l1 + mid - 1) == get(l2, l2 + mid - 1)) l = mid;
        else r = mid - 1;
    }
    return l;
}
int LCS(int l1, int r1, int l2, int r2){
    if(ch[r1] != ch[r2]) return 0;
    re int l = 1, r = min(r1 - l1 + 1, r2 - l2 + 1);
    while(l < r){
        int mid = (l + r + 1) >> 1;
        if(get(r1 - mid + 1, r1) == get(r2 - mid + 1, r2)) l = mid;
        else r = mid - 1;
    }
    return l;
}
bool le(int l1, int r1, int l2, int r2){
    if(l1 == l2) return r1 < r2;
    re int l = LCP(l1, r1, l2, r2);
    if(l1 + l > r1 || l2 + l > r2) return r1 - l1 < r2 - l2;
    return ch[l1 + l] < ch[l2 + l];
}
class PAIR{
  public: int l, r, p;
    bool operator < (const PAIR &o) const{
        return l ^ o.l ? l < o.l : (r ^ o.r ? p < o.p : r < o.r);
    }
    bool operator == (const PAIR &o) const{
        return l == o.l && r == o.r;
    } 
} runs[CN << 1]; int rcnt = 0;
PAIR mp(int a, int b, int c) {PAIR o; o.l = a, o.r = b, o.p = c; return o;}
int stk[CN], ed[CN], top;
void lyndon(){
    top = 0;
    for(re int i = n; i; i--){
        stk[++top] = i;
        while(top > 1 && le(i, stk[top], stk[top] + 1, stk[top - 1])) top--;
        ed[i] = stk[top];
    }
    for(re int i = 1; i <= n; i++){
        int j = ed[i], lcs = LCS(1, i - 1, 1, j), lcp = LCP(i, n, j + 1, n), l, r;
        l = i - lcs, r = j + lcp;
        if((r - l + 1) / (j - i + 1) > 1) runs[rcnt++] = mp(l, r, j - i + 1);
    }
}
int q, ans[CN];
class QU {
  public: int l, r, id; 
    bool operator < (const QU &o) const{
        return l ^ o.l ? l < o.l : r < o.r;
    }
} Q[CN];
int d[CN];
void md(int p, int x) {while(p <= n) d[p] = min(d[p], x), p += p & (-p);}
int qu(int p) {re int r = INF; while(p) r = min(r, d[p]), p -= p & (-p); return r;}
int main()
{
    freopen("squaren.in", "r", stdin);
    freopen("squaren.ans", "w", stdout);
    n = read(), scanf("%s", ch + 1), memset(d, 0x3f, sizeof(d));
    pB[0] = 1; for(int i = 1; i <= n; i++) pB[i] = 1ll * pB[i - 1] * B % P;
    for(re int i = 1; i <= n; i++) ha[i] = add(1ll * ha[i - 1] * B % P, ch[i] - 'a');
    lyndon();
    for(re int i = 1; i <= n; i++) ch[i] = 'a' + 'z' - ch[i];
    lyndon();
    sort(runs, runs + rcnt); int len = unique(runs, runs + rcnt) - runs;
    q = read();
    for(re int i = 1; i <= q; i++) Q[i].l = read(), Q[i].r = read(), Q[i].id = i;
    sort(Q + 1, Q + q + 1);
    for(re int p = 0, i = 1; i <= q; i++){
        re int l = Q[i].l, r = Q[i].r, mp;
        while(p < len && runs[p].l <= l){
            md(n - runs[p].r + 1, runs[p].p);
            p++;
        }
        mp = qu(n - r + 1);
        if(mp ^ INF && (r - l + 1) / mp > 1) ans[Q[i].id] = mp;
        else ans[Q[i].id] = -1;
    }
    for(re int i = 1; i <= q; i++){
        if(ans[i] == -1) puts("-1");
        else write(ans[i]), putchar('\n');
    }
    return 0;
}
