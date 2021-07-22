#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
const int CN = 2e5 + 50;
const LL INF = 0x7f7f7f7f7f7f;
LL read(){
	LL s = 0, ne = 1; char c = getchar();
	for(;c <= '0' || c > '9';c = getchar()) if(c == '-') ne = -1;
	for(;c >= '0' && c <= '9';c = getchar()) s = (s << 1) + (s << 3) + c - '0';
	return s * ne;
}
int n, m, S, T, stk[CN], top = 0; LL f[CN], g[CN]; 
vector<int> A[CN], B[CN]; vector<int> C[CN], D[CN];
LL val(int i, int j) {return g[j] - 2ll * i * j;}
class DJ {public: int id; LL v; bool operator < (const DJ &o) const {return v > o.v;}};
DJ mk(LL a, int b) {DJ c; c.id = b, c.v = a; return c;}
bool vis[CN]; priority_queue<DJ> Q;
void sp(vector<int> G[], vector<int> V[], int s, LL d[]){
	memset(vis, 0, sizeof(vis)), Q.push(mk(d[s] = 0, s));
	while(!Q.empty()){
		int u = Q.top().id; Q.pop();
		if(vis[u]) continue; vis[u] = 1;
		for(int l = G[u].size(), i = 0; i < l; i++){
			int v = G[u][i]; LL c = V[u][i]; if(vis[v]) continue;
			if(d[v] > d[u] + c) Q.push(mk(d[v] = d[u] + c, v)); 
		}
	}
}
int main()
{
	n = read(), m = read(), S = read(), T = read();
	for(int i = 1; i <= m; i++){
		int u = read(), v = read(), w = read();
		A[u].pb(v), C[u].pb(w), B[v].pb(u), D[v].pb(w);
	}
	for(int i = 1; i <= n; i++) f[i] = g[i] = INF;
	sp(A, C, S, f), sp(B, D, T, g);
	for(int i = 1; i <= n; i++) f[i] += 1ll * i * i, g[i] += 1ll * i * i;
	for(int i = 1; i <= n; i++){
		while(top > 1){
			int u = stk[top - 1], v = stk[top]; // (u, g[u]), (v, g[v]), (i, g[i])
			if(1ll * (g[v] - g[u]) * (i - v) < 1ll * (g[i] - g[v]) * (v - u)) break;
			top--;
		}
		stk[++top] = i;
	}
	int p = 1; LL ans = INF;
	for(int i = 1; i <= n; i++){
		int u = stk[p], v = stk[p + 1]; // (u, g[u]), (v, g[v])
		while(p < top && val(i, v) < val(i, u)) p++, u = v, v = stk[p + 1];
		ans = min(ans, f[i] + val(i, u));
	}
	printf("%lld", ans);
	return 0;
}
