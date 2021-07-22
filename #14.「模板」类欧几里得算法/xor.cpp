#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

#define LL long long

LL read() {
    LL s = 0, ne = 1;
    char c = getchar();
    while (c < '0' || c > '9') ne = c == '-' ? -1 : 1, c = getchar();
    while (c >= '0' && c <= '9') s = (s << 1) + (s << 3) + c - '0', c = getchar();
    return s * ne;
}

LL s2(LL n) { return 1ll * n * (n + 1) / 2; }
LL f(LL n, LL a, LL b, LL c) {
    if (!a)
        return (n + 1) * (b / c);
    if (a >= c || b >= c)
        return s2(n) * (a / c) + (n + 1) * (b / c) + f(n, a % c, b % c, c);
    LL m = (a * n + b) / c;
    return n * m - f(m - 1, c, c - b - 1, a);
}

LL n, a, d, ans, cnt[65];

int main() {
    freopen("xor.in", "r", stdin);
    freopen("xor.ans", "w", stdout);

    n = read(), a = read(), d = read();

    for (int i = 60; i + 1; i--) cnt[i] = f(n, a, d, 1ll << i) - 2 * cnt[i + 1];
    for (int i = 0; i <= 60; i++)
        if (cnt[i] & 1)
            ans |= 1ll << i;

    printf("%lld", ans);
}
