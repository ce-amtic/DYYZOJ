#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int CN = 5e5 + 10;
int read(){
    int s = 0, ne = 1; char c = getchar();
    for(;c < '0' || c > '9';c = getchar()) if(c == '-') ne = -1;
    for(;c >= '0' && c <= '9';c = getchar()) s = (s << 1) + (s << 3) + c - '0';
    return s * ne;
}
int n, m, q, c[CN], id[CN], dep[CN]; vector<int> G[CN];
namespace DMT {
    vector<int> D[CN]; queue<int> Q; int id[CN], fa[20][CN]; bool vis[CN];
    int lca(int u, int v){
        if(dep[u] < dep[v]) swap(u, v);
        for(int k = 19; k + 1; k--) if(dep[fa[k][u]] >= dep[v]) u = fa[k][u];
        if(u ^ v){
            for(int k = 19; k + 1; k--) if(fa[k][u] ^ fa[k][v])
                u = fa[k][u], v = fa[k][v];
            u = fa[0][u];
        }
        return u;
    }
    void build(){
        Q.push(1);
        while(!Q.empty()){
            int u = Q.front(); Q.pop();
            if(vis[u]) continue; vis[u] = 1, id[++id[0]] = u;
            for(int l = G[u].size(), i = 0; i < l; i++){
                int v = G[u][i]; if(vis[v]) continue;
                if(!dep[v]) dep[v] = dep[u] + 1, D[v].pb(u), Q.push(v);
                else if(dep[v] == dep[u] + 1) D[v].pb(u);
            }
        }
        for(int i = 1; i <= n; i++) G[i].clear(), dep[i] = 0; 
        dep[1] = 1;
        for(int p = 2; p <= n; p++){
            int anc = 0, i = id[p];
            for(int l = D[i].size(), j = 0; j < l; j++){
                int v = D[i][j]; if(!anc) {anc = v; continue;}
                anc = lca(anc, v);
            }
            fa[0][i] = anc, dep[i] = dep[anc] + 1, G[anc].pb(i);
            for(int k = 1; k < 20; k++) fa[k][i] = fa[k - 1][fa[k - 1][i]];
        }
    }
}
int ar[21][CN << 1], pos[CN], lg[CN << 1], idx;
void dfs(int u){
    ar[0][++idx] = u, pos[u] = idx;
    for(int l = G[u].size(), i = 0; i < l; i++){
        int v = G[u][i]; dfs(v), ar[0][++idx] = u;
    }
}
int lca(int l, int r){
    l = pos[l], r = pos[r]; if(l > r) swap(l, r);
    int g = lg[r - l + 1], e = 1 << g;
    return dep[ar[g][l]] < dep[ar[g][r - e + 1]] ? ar[g][l] : ar[g][r - e + 1];
}
class SGT {
  public: int v[CN << 2];
    #define lc k << 1
    #define rc k << 1 | 1
    void mg(int x, int y, int &u){
        if(!x) return (void)(u = y); if(!y) return (void)(u = x);
        if(x == -1 || y == -1) return (void)(u = -1);
        if(dep[x] < dep[y]) swap(x, y);
        if(lca(y, x) ^ y) return (void)(u = -1);
        u = x;
    }
    void bd(int l, int r, int k){
        if(l == r) return (void)(v[k] = id[l]);
        int m = (l + r) >> 1; bd(l, m, lc), bd(m + 1, r, rc);
        mg(v[lc], v[rc], v[k]);
    }
    void upd(int l, int r, int k, int p){
        if(l == r) return (void)(v[k] = id[l]);
        int m = (l + r) >> 1; p <= m ? upd(l, m, lc, p) : upd(m + 1, r, rc, p);
        mg(v[lc], v[rc], v[k]);
    }
    int qu(int l, int r, int k, int &u){
        if(l == r) return mg(u, v[k], u), l + !!(u ^ -1);
        int m = (l + r) >> 1, lu; mg(u, v[lc], lu);
        return lu ^ -1 ? u = lu, qu(m + 1, r, rc, u) : qu(l, m, lc, u);
    }
} D;
int main()
{
    n = read(), m = read(), q = read();
    for(int i = 1; i <= n; i++) c[i] = read(), id[c[i]] = i;
    for(int i = 1; i <= m; i++){
        int u = read(), v = read(); 
        G[u].pb(v), G[v].pb(u);
    }
    DMT :: build(), dfs(1);
    for(int i = 2; i <= idx; i++) lg[i] = lg[i >> 1] + 1;
    for(int k = 1; k <= 20; k++) for(int i = 1; i <= idx; i++){
        int j = i + (1 << (k - 1)); if(j > idx) continue;
        if(dep[ar[k - 1][i]] < dep[ar[k - 1][j]]) ar[k][i] = ar[k - 1][i];
        else ar[k][i] = ar[k - 1][j];
    }
    D.bd(0, n - 1, 1);
    while(q--){
        int u = read(), v = read(), t = 0;
        swap(c[u], c[v]), swap(id[c[u]], id[c[v]]);
        D.upd(0, n - 1, 1, c[u]), D.upd(0, n - 1, 1, c[v]), printf("%d\n", D.qu(0, n - 1, 1, t));
    }
    return 0;
}
