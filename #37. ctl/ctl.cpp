#include<bits/stdc++.h>
using namespace std;
#define mid ((l + r + 1) >> 1)
const int CN = 1e6 + 10;
const int P = 191011109;
const int B = 114; int pb[CN];
int n, ha[CN], stk[CN], top; char ch[CN];
int add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
int get(int l, int r) {return add(ha[r], P - 1ll * ha[l - 1] * pb[r - l + 1] % P);}
int LCP(int l1, int r1, int l2, int r2){
    if(ch[l1] != ch[l2]) return 0;
    int l = 1, r = min(r1 - l1 + 1, r2 - l2 + 1);
    while(l < r) get(l1, l1 + mid - 1) == get(l2, l2 + mid - 1) ? l = mid : r = mid - 1;
    return l;
}
bool le(int l1, int r1, int l2, int r2){
    int l = LCP(l1, r1, l2, r2);
    return l == r1 - l1 + 1 || l == r2 - l2 + 1 ? r1 - l1 < r2 - l2 : ch[l1 + l] < ch[l2 + l];
}
int main(){
    freopen("ctl.in", "r", stdin), freopen("ctl.ans", "w", stdout);
    scanf("%s", ch + 1), n = strlen(ch + 1), reverse(ch + 1, ch + n + 1), stk[top = 1] = n;
    pb[0] = 1; for(int i = 1; i <= n; i++) pb[i] = 1ll * pb[i - 1] * B % P;
    for(int i = 1; i <= n; i++) ha[i] = add(1ll * B * ha[i - 1] % P, ch[i] - 'a');
    for(int i = n; i; i--, stk[++top] = i) while(top > 1 && le(i, stk[top], stk[top] + 1, stk[top - 1])) top--;
    reverse(stk + 1, stk + top + 1);
    for(int i = top; i; i--) for(int j = stk[i - 1] + 1; j <= stk[i]; j++) putchar(ch[j]);
    return puts(""), 0;
}
