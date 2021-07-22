#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
#include <algorithm>
#include <vector>
#include <stack>
#define rep(i, l, r) for(int i = (l), __ = (r); i <= __; i++)
using namespace std;

struct Read_t{
	template<typename T> const Read_t & operator () ( T & target ) const {
		T x = 0 ;int sign = 1; char c = getchar();
		while(c < '0' || c > '9') { if(c == '-') sign = -1; c = getchar(); }
		while(c <= '9' && c >= '0') { x = (x << 1) + (x << 3); x += c - '0'; c = getchar(); }
		target = x * sign; return *this;
	}
}Read;

const int _ = 2040000;

vector<int> E[_];
vector<int> G[_]; int n, m;
void add(int u, int v) { /* cerr << " " << u << " " << v << endl; */ E[u].push_back(v); E[v].push_back(u); }

int dfn[_], low[_], dfc = 0, cnt = 0, tmp;
stack<int> S; vector<int> TMP;
void tarjan(int now, int f){
	dfn[now] = low[now] = ++dfc; S.push(now);
	rep(i, 0, G[now].size() - 1){ int ex = G[now][i]; if(ex == f) continue;
		if(!dfn[ex]){
			tarjan(ex, now);
			low[now] = min(low[now], low[ex]);
			if(low[ex] > dfn[now]) {
				add(now, ex); S.pop();
			}
			if(low[ex] == dfn[now]) {
				++cnt; add(cnt, now);
				do add(tmp = S.top(), cnt), S.pop(); while(tmp != ex);
			}
		} else low[now] = min(low[now], dfn[ex]);
	}
}

bool vis[_];
int dp[_][2];
int dd[_][2];
void dfs(int now, int f){
	vis[now] = 1;
	// cerr << "now = " << now << endl;
	if(now <= n){ 
		dp[now][1] = 1; dp[now][0] = 0;
		rep(i, 0, E[now].size() - 1){ int ex = E[now][i]; if(ex == f) continue;
			dfs(ex, now);
			if(ex > n) dp[now][0] += dp[ex][0], dp[now][1] += dp[ex][1];
			else {
				dp[now][1] += dp[ex][0];
				dp[now][0] += max(dp[ex][1], dp[ex][0]);
			}
		}
		// cerr << "now = " << now << " dp[now][0] = " << dp[now][0] << " dp[now][1] = " << dp[now][1] << endl;
	} else {
		rep(i, 0, E[now].size() - 1){ int ex = E[now][i]; if(ex == f) continue; dfs(ex, now); }  

		dd[1][0] = dp[E[now][1]][0]; dd[1][1] = dp[E[now][1]][1];
		rep(i, 2, E[now].size() - 1) { int ex = E[now][i]; if(ex == f) continue; // 仙人根 圆点没被选
			dd[i][1] = dd[i - 1][0] + dp[ex][1];
			dd[i][0] = max(dd[i - 1][0], dd[i - 1][1]) + dp[ex][0];
		}
		dp[now][0] = max(dd[E[now].size() - 1][0], dd[E[now].size() - 1][1]);

		dd[1][1] = dd[1][0] = dp[E[now][1]][0];
		rep(i, 2, E[now].size() - 1) { int ex = E[now][i]; if(ex == f) continue; // 仙人根 圆点被选了
			dd[i][1] = dd[i - 1][0] + dp[ex][1];
			dd[i][0] = max(dd[i - 1][0], dd[i - 1][1]) + dp[ex][0];
		}
		dp[now][1] = dd[E[now].size() - 1][0];
		// cerr << "now = " << now << " dp[now][0] = " << dp[now][0] << " dp[now][1] = " << dp[now][1] << endl;
	}
}

int main(){ // freopen(".in", "r", stdin);
	Read(n)(m); cnt = n;
	rep(i, 1, m){
		int u, v; Read(u)(v);
		G[u].push_back(v); G[v].push_back(u);
	}
	rep(i, 1, n) if(!dfn[i]) tarjan(i, i);
	// for(int i = 1; i <= cnt; i++){
		// cerr << "now i = " << i << endl;
		// rep(j, 0, E[i].size() - 1) cerr << E[i][j] << " "; cerr << endl;
	// }

	int ans = 0;

	memset(vis, 0, sizeof(vis));
	rep(i, 1, n) if(!vis[i]) dfs(i, i), ans += max(dp[1][0], dp[1][1]);

	printf("%d\n", ans);
	return 0;
}
