#include<bits/stdc++.h>
using namespace std;
#define pb push_back
const int CN = 5e5 + 10;
int read(){
	int s = 0, ne = 1; char c = getchar();
	for(;c < '0' || c  > '9';c = getchar()) if(c == '-') ne = -1;
	for(;c >= '0' && c <= '9';c = getchar()) s = (s << 3) + (s << 1) + c - '0';
	return s * ne;
}
int n, k, fa[CN], dep[CN], id[CN], mdis[CN];
bool cmp(int i, int j) {return dep[i] > dep[j];}
int main()
{
	n = read(), k = read();
	dep[1] = 1;
	for(int i = 2; i <= n; i++) fa[i] = read(), dep[i] = dep[fa[i]] + 1;
	for(int i = 1; i <= n; i++) id[i] = i, mdis[i] = 1e9;
	sort(id + 1, id + n + 1, cmp);
	int ans = 0;
	for(int p = 1; p <= n; p++){
		int i = id[p], pos = i; bool flag = 0;
		for(int b = 0; pos && !flag && b <= k; b++){
			if(mdis[pos] + dep[i] - dep[pos] <= k) flag = 1;
			pos = fa[pos];
		}
		if(flag) continue;
		pos = i;
		for(int b = 1; pos ^ 1 && b <= k; b++) pos = fa[pos];
		mdis[pos] = 0;
		for(int j = i; j ^ pos; j = fa[j]) mdis[j] = min(mdis[j], dep[j] - dep[pos]);
		for(int b = 1, j = fa[pos]; b <= k && j; b++, j = fa[j]) 
		    mdis[j] = min(mdis[j], dep[pos] - dep[j]);
		ans++;
	}
	printf("%d", ans);
	return 0;
}
