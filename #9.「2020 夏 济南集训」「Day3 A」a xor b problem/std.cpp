#include<bits/stdc++.h>
//#pragma gcc optimize(3)
#define gc getchar()
//char buf[100000],*buff = buf + 100000;
//#define gc ((buff == buf + 100000 ? (fread(buf,1,100000,stdin),buff = buf) : 0),*(buff++))
#define pc putchar
//char bfu[100000000],*bfuu = bfu;
//#define pc(x) (*(bfuu++) = x)
#define li long long
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define md int mid = l + r >> 1
#define ls q << 1
#define rs q << 1 | 1
#define ln ls,l,mid
#define rn rs,mid + 1,r
using namespace std;
const int mo = 998244353;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
// inline void file(char *s){
// 	char c[50];
// 	sprintf(c,"%s.in",s);
// 	freopen(c,"r",stdin);
// 	sprintf(c,"%s.out",s);
// 	freopen(c,"w",stdout);
// }
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
inline li ksm(li q,li w){
	li as = 1;
	while(w){
		if(w & 1) as = as * q % mo;
		q = q * q % mo;
		w >>= 1;
	}
	return as;
}
vector<li> wn[2][20];
char ch[100010];
struct gjd{
	vector<int> a;
	int d; 
	inline int& operator [](int x){return a[x];}
	inline gjd read(int dd){
		d = dd;
		int tp = 0;
		ch[0] = gc;
		while(ch[0] < '0' || ch[0] > '9') ch[0] = gc;
		while(ch[tp] >= '0' && ch[tp] <= '9') ch[++tp] = gc;
		if(tp == 1 && ch[0] == '0') return *this;
		a.resize(tp);
		for(int i = 0;i < tp;++i) a[i] = ch[tp - i - 1] - '0'; 
		return *this;	
	}
	inline int size(){return a.size();}
	inline void print(){
		if(!size()) pc('0');
		for(int i = size();i;--i) pc(a[i - 1] + '0');
	}
};
inline gjd fz(li x,int d){
	gjd a;
	a.d = d;
	while(x){
		a.a.pb(x % d);x /= d;
	}
	return a;
}
inline gjd operator ^ (gjd x,gjd y){
	int d = x.d,i;
	if(x.size() < y.size()) swap(x,y);
	for(i = 0;i < y.size();++i) x[i] = (x[i] + y[i] < d ? x[i] + y[i] : x[i] + y[i] - d);
	i = x.size();while(i && !x[i - 1]) x.a.pop_back(),--i;
	return x; 
}
inline gjd operator + (gjd x,gjd y){
	int d = x.d,i;
	if(x.size() < y.size()) swap(x,y);
	for(i = 0;i < y.size();++i) x[i] += y[i];
	for(i = 0;i + 1 < x.size();++i) if(x[i] >= d) x[i] -= d,++x[i + 1];
	if(i >= 0 && x[i] >= d) x[i] -= d,x.a.pb(1);
	return x;
}
gjd x,xx,y,yy,z,zz;
int a,b,tp[525000];
li tp1[525000],tp2[525000],tp3[525000];
inline void qwq(li *q,int l,bool fg){
	register int i,j,k,p;
	li q1,qq;
	for(i = 1;i < l;++i) if(i < tp[i]) swap(q[i],q[tp[i]]);
	for(i = 1,p = 1;i < l;i <<= 1,++p){
		for(j = 0;j < l;j += (i << 1)){
			for(k = 0;k < i;++k){
				q1 = q[j + k],qq = q[j + k + i] * wn[fg][p][k] % mo;
				q[j + k] = (q1 + qq >= mo) ? q1 + qq - mo : q1 + qq; 
				q[j + k + i] = (q1 - qq < 0) ? q1 - qq + mo : q1 - qq;
			}
		}
	}
	if(fg){
		li nn = ksm(l,mo - 2);
		for(i = 0;i < l;++i) (q[i] *= nn) %= mo; 
	}
}
int q0[11] = {0,0,24,15,12,10,9,8,8,7,7},p0[11];
inline gjd operator * (gjd x,gjd y){
	if(!x.size()) return x;
	if(!y.size()) return y;
	register int i,j,k,o;
	int d = x.d,ml = min(x.size(),y.size());
	if(ml / q0[d] <= 5000){
		int l1,l2,tmp;
		for(i = 0,j = 0,l1 = 0,tmp = 1;i < x.size();++i){
			if(j == q0[d]) j = 0,tmp = 1,++l1;
			tp1[l1] += x[i] * tmp;
			++j;tmp *= d;
		}
		for(i = 0,j = 0,l2 = 0,tmp = 1;i < y.size();++i){
			if(j == q0[d]) j = 0,tmp = 1,++l2;
			tp2[l2] += y[i] * tmp;
			++j;tmp *= d;
		}
		for(i = 0;i <= l1;++i) for(j = 0;j <= l2;++j) tp3[i + j] += tp1[i] * tp2[j];
		for(i = 0;i <= l1 + l2;++i) tp3[i + 1] += tp3[i] / p0[d],tp3[i] %= p0[d];
		for(;tp3[i] >= p0[d];++i) tp3[i + 1] += tp3[i] / p0[d],tp3[i] %= p0[d];
		int ll = i + 1;
		gjd z;z.d = d;z.a.resize(ll * q0[d]);
		for(i = 0,j = 0,k = 0;i < z.size();++i){
			z[i] = tp3[k] % d;
			tp3[k] /= d;++j;
			if(j == q0[d]) ++k,j = 0;
		}
		i = z.size();while(i && !z[i - 1]) z.a.pop_back(),--i;
		for(i = 0;i < z.size();++i) tp1[i] = tp2[i] = tp3[i] = 0;
		return z;
	}
	for(i = 0;i < x.size();++i) tp1[i] = x[i];
	for(i = 0;i < y.size();++i) tp2[i] = y[i];
	for(o = x.size() + y.size(),j = 1,k = 0;j < o;j <<= 1,++k);
	for(i = 1;i < j;++i) tp[i] = (tp[i >> 1] >> 1) | ((i & 1) << (k - 1));
	qwq(tp1,j,0);qwq(tp2,j,0);for(i = 0;i < j;++i) tp3[i] = tp1[i] * tp2[i] % mo;qwq(tp3,j,1);
	for(i = 0;i < j;++i) tp3[i + 1] += tp3[i] / d,tp3[i] %= d;
	for(;tp3[i] >= d;++i) tp3[i + 1] += tp3[i] / d,tp3[i] %= d;
	for(++i;i && !tp3[i - 1];--i);
	gjd z;z.d = x.d;z.a.resize(i);
	for(k = i - 1;k >= 0;--k) z[k] = tp3[k];
	for(k = 0;k < i || k < j;++k) tp1[k] = tp2[k] = tp3[k] = 0;
	return z;
}
gjd pp[25];
gjd trs(gjd x,int d){
	if(!x.size()){x.d = d;return x;}
	if(x.size() <= 18){
		li as = 0;
		int dd = x.d,i;
		for(i = x.size();i;--i) (as *= dd) += x[i - 1];
		return fz(as,d);
	}
	int i,j,k;
	for(i = 1,j = 0;(i << 1) < x.size();i <<= 1,++j);
	gjd t1,t2;t1.d = t2.d = x.d;
	t1.a.resize(i);t2.a.resize(x.size() - i);
	for(k = 0;k < i;++k) t1[k] = x[k];
	for(;k < x.size();++k) t2[k - i] = x[k];
	k = t1.size();while(k && !t1[k - 1]) t1.a.pop_back(),--k;
	return trs(t1,d) + pp[j] * trs(t2,d);
}
int main(){
	srand(time(0));rd();
	//file("xor");
	int i,j,k;
	for(i = 2;i <= 10;++i) p0[i] = ksm(i,q0[i]);
	for(i = 1;i <= 19;++i){
		j = 1 << i;
		wn[0][i].resize(j);wn[1][i].resize(j);
		wn[0][i][0] = wn[1][i][0] = 1;
		wn[0][i][1] = ksm(3,(mo - 1) / j);
		for(k = 2;k < j;++k) wn[0][i][k] = wn[0][i][k - 1] * wn[0][i][1] % mo;
		for(k = 1;k < j;++k) wn[1][i][k] = wn[0][i][j - k]; 
	}
	a = read();b = read();
	x.read(a);y.read(a);
	if(!x.size()){y.print();return 0;}
	if(!y.size()){x.print();return 0;}
	pp[0] = fz(a,b);
	for(k = max(x.size(),y.size()),i = 1,j = 0;i < k;i <<= 1,++j);
	for(k = 1;k <= j;++k) pp[k] = pp[k - 1] * pp[k - 1];
	xx = trs(x,b);yy = trs(y,b);
	zz = xx ^ yy;
	pp[0] = fz(b,a);
	for(k = zz.size(),i = 1,j = 0;i < k;i <<= 1,++j);
	for(k = 1;k <= j;++k) pp[k] = pp[k - 1] * pp[k - 1];
	z = trs(zz,a);
	z.print();pc('\n');
	//fwrite(bfu,1,bfuu - bfu,stdout);
	//cerr<<clock()<<endl;
	return 0;
}
