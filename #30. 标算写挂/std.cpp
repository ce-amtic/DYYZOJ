#include<bits/stdc++.h>
using namespace std;
#define int long long
const int P = 1004535809;
int read(){
    int s = 0, ne = 1; char c = getchar();
    for(;c < '0' || c > '9';c = getchar()) if(c == '-') ne = -1;
    for(;c >= '0' && c <= '9';c = getchar()) s = (s << 1) + (s << 3) + c - '0';
    return s * ne;
}
int mul(int a, int b, int P) {
    return (a % P) * (b % P) % P;
}
int qp(int a, int b, int P){
    a %= P, b %= P; int r = 1;
    while(b){
        if(b & 1) r = mul(r, a, P);
        a = mul(a, a, P), b >>= 1;
    }
    return r;
}
int gcd(int a, int b) {return a >= 0 ? (b ? gcd(b, a % b) : a) : gcd(-a, b);}
namespace PR {
    const int pri[25] = {20, 2, 3, 5, 7, 9, 11, 13, 17, 19, 23, 29, 31, 47, 113, 127, 131, 151, 313, 317, 409};
    bool mr(int n){
        if(n < 2) return 0; if(n == 2) return 1; if(!(n & 1)) return 0;
        int s = 0, t = n - 1;
        while(!(t & 1)) t >>= 1, s++; 
        for(int i = 1; i <= pri[0]; i++){
            if(pri[i] >= n) return 1;
            int x = qp(pri[i], t, n), j = 0; 
            if(x == 1) continue;
            while(j < s && (x ^ (n - 1))) x = mul(x, x, n), j++; 
            if(j == s) return 0;
        }
        return 1;
    }
    int pr(int n){ 
        int x, y, i = 1, k = 2, c = rand() % (n - 1) + 1; 
        x = y = rand() % (n - 1) + 1;
        while(1){
            x = (mul(x, x, n) + c) % n;
            int d = gcd(y - x, n);
            if(1 < d && d < n) return d;
            if(x == y) return n;
            if((++i) == k) y = x, k <<= 1;
        }
    }
    void fac(int n, int res[]){
        if(n == 1) return;
        if(mr(n)) return (void)(res[++res[0]] = n); 
        int p = n; 
        while(p >= n) p = pr(p);
        while(!(n % p)) n /= p;
        fac(p, res), fac(n, res);
    }
}
int n, m, r[101], a[101], t[101], N; int ans = 0;
void get(int n){
    PR :: fac(n, r);
    sort(r + 1, r + r[0] + 1), N = 1;
    for(int i = 2; i <= r[0]; i++) if(r[i] ^ r[i - 1]) r[++N] = r[i];
    r[0] = N;
    for(int i = 1; i <= N; i++){
        while(!(n % r[i])) a[i]++, n /= r[i];
    }
}
int phi(int x){
    if(x == 1) return 1;
    t[0] = 0, PR :: fac(x, t);
    sort(t + 1, t + t[0] + 1);
    int n = 1;
    for(int i = 2; i <= t[0]; i++) if(t[i] ^ t[i - 1]) t[++n] = t[i];
    t[0] = n;
    for(int i = 1; i <= t[0]; i++) x /= t[i], x *= (t[i] - 1);
    return x % P;
}
void dfs(int pos, int d){
    if(pos > N){
        int cur = 1ll * qp(m, d, P) * (gcd(m, n / d) % P) % P;
        ans = (1ll * cur * phi(n / d) % P + ans) % P;
        return;
    }
    int u = 1;
    for(int i = 0; i <= a[pos]; i++) dfs(pos + 1, d * u), u *= r[pos];    
}
signed main()
{
    int *seed = new int; srand(time(0) + clock() + *seed);
    n = read(), m = read(), get(n);
    dfs(1, 1), ans = 1ll * ans * qp(mul(n, m, P), P - 2, P) % P;
    printf("%lld", ans);
    return 0;
}
