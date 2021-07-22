#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define iter set<PAIR> :: iterator
const int CN = 5e5 + 50;
int read(){
    int s = 0, ne = 1; char c = getchar();
    while(c < '0' || c > '9') {if(c == '-') ne = -1; c = getchar();}
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}
class PAIR {
  public: int x, y;
    bool operator < (const PAIR &o) const {return x ^ o.x ? x < o.x : y < o.y;}
};
PAIR mp(int a, int b) {PAIR o; o.x = a, o.y = b; return o;}
set<PAIR> S; vector<PAIR> Q[CN];
int n, m, L[CN], R[CN], ans[CN];
class BIT {
  public: int d[CN];
    void add(int p, int x) {while(p <= n) d[p] += x, p += p & (-p);}
    void md(int l, int r, int x) {add(l, x), add(r + 1, -x);}
    int qu(int p) {int r = 0; while(p) r += d[p], p -= p & (-p); return r;}
} D;
int main()
{
	freopen("cover.in", "r", stdin);
	freopen("cover.out", "w", stdout);
	n = read(), m = read();
	for(int i = 1; i <= n; i++) L[i] = read(), R[i] = read();
	for(int i = 1; i <= m; i++){
		int l = read(), r = read();
		Q[r].pb(mp(l, i));
	}
	S.insert(mp(1e9, 0));
	for(int i = 1; i <= n; i++){
		int l = L[i], r = R[i], fst = -1, prv = l - 1;
		iter it = S.lower_bound(mp(l - 1, 0));
		while(1){
			if(it == S.end()) break;
			int cur = (*it).x, p = (*it).y, len;
			if(fst < 0) fst = p;
			len = min(cur, r) - prv, D.md(p + 1, i, len);
			if(cur <= r){
				prv = cur;
				iter pit = it; it++, S.erase(pit);
			}
			else break;
		}
		if(l > 1) S.insert(mp(l - 1, fst));
		S.insert(mp(r, i));
		for(int l = Q[i].size(), j = 0; j < l; j++)
		    ans[Q[i][j].y] = D.qu(Q[i][j].x);
	}
	for(int i = 1; i <= m; i++) printf("%d", ans[i]), puts("");
	return 0;
}
