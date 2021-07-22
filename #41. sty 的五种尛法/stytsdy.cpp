#include<bits/stdc++.h>
using namespace std; typedef long long LL; const int P = 1004535809, CN = 4e5 + 10;
int K, n, a, fac[CN], ifac[CN], pre[CN], suf[CN];
int C(int n, int m) {return m < 0 || m > n ? 0 : (LL)fac[n] * ifac[m] % P * ifac[n - m] % P;}
int qp(int a, int b){
    int r = 1;
    for(; b; b >>= 1, a = (LL)a * a % P) if(b & 1) r = (LL)r * a % P;
    return r;
}
void work(){
    if(a < 0) return (void)printf("0\n");
    int yi = 0, ans = 0, N = a + K + 2;
    pre[0] = suf[N + 1] = 1;
    for(int i = 1; i <= N; i++) pre[i] = (LL)pre[i - 1] * (n - i) % P;
    for(int i = N; i; i--) suf[i] = (LL)suf[i + 1] * (n - i) % P;
    for(int i = 1; i <= N; i++){
        yi = (yi + (LL)C(i, a) * qp(i, K)) % P; int tmp;
        tmp = (LL)yi * ifac[i - 1] % P * ifac[N - i] % P * pre[i - 1] % P * suf[i + 1] % P;
        ans = (N - i) & 1 ? (ans - tmp + P) % P : (ans + tmp) % P;
    }
    printf("%d\n", ans);
}
int main(){
    freopen("stytsdy.in", "r", stdin);
    freopen("stytsdy.ans", "w", stdout);
    scanf("%d%d%d", &K, &n, &a), fac[0] = ifac[0] = ifac[1] = 1;
    for(int i = 2; i <= 400005; i++) ifac[i] = (LL)ifac[P % i] * (P - P / i) % P;
    for(int i = 1; i <= 400005; i++) ifac[i] = (LL)ifac[i - 1] * ifac[i] % P, fac[i] = (LL)fac[i - 1] * i % P;
    work(); fclose(stdin); fclose(stdout); return 0;
}
