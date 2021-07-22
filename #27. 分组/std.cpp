#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
const int CN = 1e5 + 10;
const int CM = 1e6 + 10;
int read(){
    int s = 0, ne = 1; char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') ne = -1; c = getchar();}
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}
int n, m, X[CM], Y[CM]; vector<int> G[CN], S;
int dfn[CN], low[CN], idx, stk[CN], top; bool ins[CN];
LL B, cur;
void tarjan(int u){
    dfn[u] = low[u] = ++idx, stk[++top] = u, ins[u] = 1;
    for(int l = G[u].size(), i = 0; i < l; i++){
        int v = G[u][i]; 
        if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if(ins[v]) low[u] = min(low[u], low[v]);
    }
    if(low[u] == dfn[u]){
        int cnt = 0, pos = 0;
        while(pos ^ u) pos = stk[top--], cnt++, ins[pos] = 0;
        cur += 1ll * cnt * cnt;
    }
}
bool ck(int L, int R){
    R = min(R, m);
    for(int i = L; i <= R; i++) 
        G[X[i]].pb(Y[i]), S.pb(X[i]), dfn[X[i]] = dfn[Y[i]] = 0;
    int l = S.size(); cur = n;
    for(int i = 0; i < l; i++) 
        if(!dfn[S[i]]) idx = 0, tarjan(S[i]), cur -= idx;
    for(int i = L; i <= R; i++) G[X[i]].clear(); S.clear();
    return cur <= B;
}
int main()
{
    n = read(), m = read(), B = read();
    for(int i = 1; i <= m; i++) X[i] = read(), Y[i] = read();
    int ans = 0;
    for(int L = 1; L <= m; L++){
        int k = 0;
        while(ck(L, L + (1 << k) - 1)){
            if(L + (1 << k) - 1 > m) break;
            k++;
        }
        int l = L + (1 << (k - 1)) - 1, r = min(m, L + (1 << k) - 1);
        while(l < r){
            int mid = (l + r + 1) >> 1;
            if(ck(L, mid)) l = mid;
            else r = mid - 1;
        }
        L = l, ans++;
    }
    printf("%d", ans);
    return 0;
}
