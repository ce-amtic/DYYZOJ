#include<bits/stdc++.h>
//#pragma gcc optimize(3)
//#define gc getchar()
char buf[100000],*buff = buf + 100000;
#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
char bfu[10000000],*bfuu = bfu;
#define pc(x) (*(bfuu++) = x)
#define li long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define pli pair<li,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
inline int read(){
	int x = 0,c = gc;
	while(c < '0' || c > '9') c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return x;
}
inline void print(int x){
	if(x >= 10) print(x / 10);
	pc(x % 10 + '0');
}

inline void file(char *s){
	char c[50];
	sprintf(c,"%s.in",s);
	freopen(c,"r",stdin);
	sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
int n,m,q;
struct edge{
	int u,v,w;
}e[500010];
int fe[300010],fp[300010],ans[300010];
inline int getfe(int q){
	return fe[q] == q ? q : fe[q] = getfe(fe[q]);
}
inline int getfp(int q){
	return fp[q] == q ? q : fp[q] = getfp(fp[q]);
}
inline void mge(int u,int v){
	fe[getfe(u)] = getfe(v);
}
inline void mgp(int u,int v){
	fp[getfp(u)] = getfp(v);
}
inline bool operator < (edge q,edge w){
	return q.w > w.w;
}
vector<int> e0[300010];
vector<pii> p0[300010];
//const int mo = 1000033;
const int mo = 3000017;
const li s1 = 19260817;
int cnt;
struct ha1{
	vector<li> a[mo];
	inline void ins(int u,int v){
		if(u > v) swap(u,v);
		li vl = u * s1 + v;
		int vm = vl % mo;
		for(int i = 0;i < a[vm].size();++i) if(a[vm][i] == vl) return;
		a[vm].pb(vl);
	}
	inline bool qy(int u,int v){
		if(u > v) swap(u,v);
		li vl = u * s1 + v;
		int vm = vl % mo;
		for(int i = 0;i < a[vm].size();++i) if(a[vm][i] == vl) return 1;
		return 0;
	}
}ee;
vector<int> p2[1000010];
struct ha2{
	vector<pli> a[mo];
	inline void ins(int u,int v,int id){
		if(u > v) swap(u,v);
		li vl = u * s1 + v;
		int vm = vl % mo;
		for(int i = 0;i < a[vm].size();++i) if(a[vm][i].fi == vl){
			p2[a[vm][i].se].pb(id);return;
		}
		p2[++cnt].pb(id);a[vm].pb(mp(vl,cnt));return;
	}
	inline int qy(int u,int v){
		if(u > v) swap(u,v);
		li vl = u * s1 + v;
		int vm = vl % mo;
		for(int i = 0;i < a[vm].size();++i) if(a[vm][i].fi == vl) return a[vm][i].se;
		return 0;
	}
}pp;
int main(){
//	file("truck");
	int i,j,k,u,v,ue,up,ve,vp,o;
	n = read();m = read();q = read();
	for(i = 1;i <= n;++i) fe[i] = fp[i] = i;
	for(i = 1;i <= m;++i){
		e[i].u = read();e[i].v = read();e[i].w = read();
	}
	sort(e + 1,e + m + 1);
	for(i = 1;i <= m;++i){
		if(e[i].u == e[i].v) continue;
		ee.ins(e[i].u,e[i].v);
		e0[e[i].u].pb(e[i].v);e0[e[i].v].pb(e[i].u);
	}
	for(i = 1;i <= q;++i){
		u = read();v = read();
		//if(u == v || ee.qy(u,v)){ans[i] = -1;continue;} 
		pp.ins(u,v,i);
		p0[u].pb(mp(v,i));p0[v].pb(mp(u,i));
	}
	
	for(i = 1;i <= m;++i){
		ue = getfe(e[i].u);ve = getfe(e[i].v);
		up = getfp(e[i].u);vp = getfp(e[i].v);
		if(ue == ve) continue;
		if(e0[ue].size() < p0[vp].size()){
			for(j = 0;j < e0[ue].size();++j){
				u = getfp(e0[ue][j]);
				v = pp.qy(vp,u);
				for(k = 0;k < p2[v].size();++k) if(!ans[p2[v][k]]) ans[p2[v][k]] = e[i].w;
			}
		}
		else{
			for(j = 0;j < p0[vp].size();++j){
				u = p0[vp][j].se;
				if(ans[u]) continue;
				v = getfe(p0[vp][j].fi);
				if(ee.qy(ue,v)) ans[u] = e[i].w;
			}
		}
		
		if(e0[ve].size() < p0[up].size()){
			for(j = 0;j < e0[ve].size();++j){
				u = getfp(e0[ve][j]);
				v = pp.qy(up,u);
				for(k = 0;k < p2[v].size();++k) if(!ans[p2[v][k]]) ans[p2[v][k]] = e[i].w;
			}
		}
		else{
			for(j = 0;j < p0[up].size();++j){
				u = p0[up][j].se;
				if(ans[u]) continue;
				v = getfe(p0[up][j].fi);
				if(ee.qy(ve,v)) ans[u] = e[i].w;
			}
		}
		
		if(e0[ue].size() > e0[ve].size()) swap(ue,ve);
		for(j = 0;j < e0[ue].size();++j){
			u = getfe(e0[ue][j]);
			if(ve == u || ue == u) continue;
			e0[ve].pb(u);
			ee.ins(ve,u);
		}
		mge(ue,ve);
		
		if(p0[up].size() > p0[vp].size()) swap(up,vp);
		for(j = 0;j < p0[up].size();++j){
			o = p0[up][j].se;
			if(ans[o]) continue;
			u = getfp(p0[up][j].fi);
			p0[vp].pb(mp(u,o));
			pp.ins(vp,u,o);
		} 
		mgp(up,vp);
	}
	//for(i = 1;i <= q;++i) if(ans[i] <= 0) ans[i] = ~ans[i];
	for(i = 1;i <= q;++i) print(ans[i]),pc('\n'); 
	fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<" "<<cnt;
	return 0;
}
