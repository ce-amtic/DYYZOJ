#include<bits/stdc++.h>
using namespace std;
#define LL long long
#define pb push_back
const int CN = 5e4 + 40;
const int H = 60;
LL read(){
	LL s = 0, ne = 1; char c = getchar();
	for(;c < '0' || c > '9';c = getchar()) if(c == '-') ne = -1;
	for(;c >= '0' && c <= '9';c = getchar()) s = (s << 1) + (s << 3) + c - '0';
	return s * ne;
}
int n, q; LL a[CN], val[CN]; bitset<CN> T[70]; bool ans[CN * 100];
class QU {public: int id, rk;}; vector<QU> Q[CN];
QU mk(int a, int b) {QU o; o.id = a, o.rk = b; return o;}
class TIRE {
  public: int sz[CN * 100], ch[CN * 100][2], idx, rt;
    #define lc ch[u][0]
    #define rc ch[u][1]
    void ins(int &u, int dep, LL x){
    	if(!u) u = ++idx;
    	if(dep < 0) return (void)(sz[u]++);
    	ins(ch[u][(x >> dep) & 1], dep - 1, x);
    	sz[u] = sz[lc] + sz[rc];
	}
	void dfs(int u, int dep, int pos, int top){
		if(dep < 0){
			for(int l = Q[pos].size(), i = 0; i < l; i++)
				ans[Q[pos][i].id] = T[top][Q[pos][i].rk];
			return;
		}
		if(rc){
			bool b = 0;
		 	if(lc) b = 1, T[top + 1] = T[top] | (T[top] << sz[lc]);
		 	dfs(rc, dep - 1, pos + sz[lc], top + b);
		}
		if(lc){
			bool b = 0;
			if(rc) b = 1, T[top + 1] = T[top] | (T[top] << sz[rc]);
			dfs(lc, dep - 1, pos, top + b);
		}
	}
} D;
int main()
{
	n = read(), q = read();
	for(int i = 1; i <= n; i++) val[i] = a[i] = read();
	sort(val + 1, val + n + 1);
	for(int i = 1; i <= n; i++) D.ins(D.rt, H, a[i]);
	for(int i = 1; i <= q; i++){
		int x = read(), y = read(), 
		    u = lower_bound(val + 1, val + n + 1, a[x]) - val;
		Q[u].pb(mk(i, y));
	}
	T[1][1] = 1, D.dfs(D.rt, H, 1, 1);
	for(int i = 1; i <= q; i++) putchar("01"[ans[i]]);
	return 0;
}
