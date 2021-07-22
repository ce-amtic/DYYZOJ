#include<cstdio>
const int P = 998244353, CN = 2e5 + 10, i2 = (P + 1) >> 1;
int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
int n, fac[CN], ifac[CN], pw[CN], ans;
int main(){
    freopen("sb.in", "r", stdin), freopen("sb.out", "w", stdout);
    scanf("%d", &n), fac[0] = ifac[0] = ifac[1] = pw[0] = 1;
    for(int i = 2; i <= n; i++) ifac[i] = 1ll * ifac[P % i] * (P - P / i) % P;
    for(int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % P, ifac[i] = 1ll * ifac[i - 1] * ifac[i] % P;
    ans = 1ll * fac[n - 1] * i2 % P; for(int i = 1; i <= n; i++) pw[i] = 1ll * pw[i - 1] * n % P;
    for(int l = 3; l < n; l++) ans = add(ans, 1ll * i2 * fac[n] % P * ifac[n - l] % P * pw[n - l - 1] % P);
    return printf("%d\n", ans), 0;
}
