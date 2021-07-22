#include<bits/stdc++.h>
using namespace std;
#define lc ch[u][0]
#define rc ch[u][1]
const int CN = 1e5 + 10;
int read(){
    int s = 0, ne = 1; char c = getchar();
    for(; c < '0' || c > '9'; c = getchar()) if(c == '-') ne = -1;
    for(; c >= '0' && c <= '9'; c = getchar()) s = (s << 1) + (s << 3) + c - '0';
    return s * ne;
}
int n, q, pos[CN], pb[CN], len[CN << 2], nxt[CN << 2], fa[20][CN << 2], son[CN << 2][26], idx; char S[CN], T[CN];
void ins(char ch[], bool tp){
    for(int i = 1, u = 0, c; c = ch[i] - 'a', ch[i]; i++){
        if(!son[u][c]) son[u][c] = ++idx; u = son[u][c];
        if(tp) pos[i] = u; else pb[i] = u;
    }
}
int et(int p, int c){
    int u = son[p][c]; if(len[u]) return u; len[u] = len[p] + 1, p = nxt[p];
    while(p ^ -1 && !son[p][c]) son[p][c] = u, p = nxt[p];
    if(p == -1) return u; int d = son[p][c];
    if(len[d] == len[p] + 1) return nxt[u] = d, u;
    int v = ++idx; len[v] = len[p] + 1, nxt[v] = nxt[d], nxt[d] = nxt[u] = v;
    for(int i = 0; i < 26; i++) if(len[son[d][i]]) son[v][i] = son[d][i];
    while(p ^ -1 && son[p][c] == d) son[p][c] = v, p = nxt[p];
    return u;
}
class PAIR {public: int x, y;}; queue<PAIR> Q;
PAIR mp(int a, int b) {PAIR o; o.x = a, o.y = b; return o;}
void bd(){
    for(int i = 0; i < 26; i++) if(son[0][i]) Q.push(mp(0, i));
    while(!Q.empty()){
        int u = Q.front().x, c = Q.front().y; Q.pop(), u = et(u, c);
        for(int i = 0; i < 26; i++) if(son[u][i]) Q.push(mp(u, i));
    }
}
int rt[CN << 2], ch[CN * 70][2], cnt[CN], id[CN << 2], sidx; bool d[CN * 70];
void md(int &u, int l, int r, int p){
    if(!u){
    u = ++sidx; assert(sidx < CN * 70);
    }
    if(l == r) return (void)(d[u] |= 1);
    int m = (l + r) >> 1; p <= m ? md(lc, l, m, p) : md(rc, m + 1, r, p);
    d[u] = d[lc] | d[rc];
}
int mg(int x, int y, int l, int r){
    if(!(x * y)) return x + y; int u = ++sidx, m = (l + r) >> 1;
    d[u] = d[x] | d[y]; if(l == r) return u;
    lc = mg(ch[x][0], ch[y][0], l, m), rc = mg(ch[x][1], ch[y][1], m + 1, r);
    d[u] = d[lc] | d[rc]; return u;
}
int qu(int u, int l, int r, int s, int t){
    if(!d[u]) return 0; if(l == r) return l; int m = (l + r) >> 1, tmp;
    if(s <= m) {tmp = qu(lc, l, m, s, t); if(tmp) return tmp;}
    return m < t ? qu(rc, m + 1, r, s, t) : 0;
}
int main(){
    nxt[0] = -1, scanf("%s%s", S + 1, T + 1), n = strlen(S + 1), ins(S, 1), ins(T, 0), bd();
    for(int i = 1; i <= n; i++) md(rt[pos[i]], 1, n, i);
    for(int i = 1; i <= idx; i++) cnt[len[i]]++; for(int i = n; i; i--) cnt[i] += cnt[i + 1];
    for(int i = 1; i <= idx; i++) id[cnt[len[i]]--] = i;
    for(int p = 1, i; i = id[p], p <= idx; p++) if(nxt[i]) rt[nxt[i]] = mg(rt[nxt[i]], rt[i], 1, n);
    memcpy(fa[0], nxt, sizeof(nxt)), fa[0][0] = 0;
    for(int k = 1; k < 20; k++) for(int i = 1; i <= idx; i++) fa[k][i] = fa[k - 1][fa[k - 1][i]];
    q = read(); while(q--){
        int l = read(), r = read(), s = read(), t = read(), u = pb[t];
        for(int k = 19; k + 1; k--) if(len[fa[k][u]] >= t - s + 1) u = fa[k][u];
        if(t - s > r - l) puts("0");
        else printf("%d\n", max(0, qu(rt[u], 1, n, l + t - s, r) - t + s));
    }
    return 0;
}
