#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;

#define LL long long

const int CN = 1e6+6;
const int P = 100019;

LL read(){
    LL s = 0, ne = 1; char c = getchar();
    while(c < '0' || c > '9') ne = c == '-' ? -1 : 1, c = getchar();
    while(c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}

int qp(int a,int b) {int r = 1; while(b) {if(b & 1) r = 1ll * r * a % P; a = 1ll * a * a % P; b >>= 1;} return r;}

int fac[CN], ifac[CN];
int C(int n, int m) {
    int r = 1ll * fac[n] * ifac[n - m] % P;
    return 1ll * r * ifac[m] % P;
}
int lucas(LL n, LL m) {
    if(!n) return 1;
    return 1ll * C(n % P, m % P) * lucas(n / P, m / P) % P;
}
int f(LL n) {
    return lucas(n + 9, n);
}

LL n;

int main()
{
    freopen("num.in", "r", stdin);
    freopen("num.ans", "w", stdout);
    n = read();
    fac[0] = fac[1] = ifac[0] = 1;
    for(int i = 2; i < P; i++){
    	fac[i] = 1ll * fac[i - 1] * i % P;
        if(!fac[i]) {printf("%d", i);break;}
	}
    ifac[P - 1] = qp(fac[P - 1], P - 2);
    for(int i = P - 2; i; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P; 
    
    int ans = (f(n) - f(n - 1) + P) % P;
    printf("%d", ans);
}
