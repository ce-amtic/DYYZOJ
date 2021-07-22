#include<bits/stdc++.h>
using namespace std;
#define rint register int
#define iint inline int
const int P = 1004535808;
const int CN = 1e5 + 10;
iint read(){
	rint s = 0, ne = 1; char c = getchar();
	for(;c < '0' || c > '9';c = getchar()) if(c == '-') ne = -1;
	for(;c >= '0' && c <= '9';c = getchar()) s = (s << 1) + (s << 3) + c - '0';
	return s * ne;
}
iint add(int x, int y) {return x + y >= P ? x + y - P : x + y;}
int n, m, f[20][CN], C[101][101];
int main()
{
	n = read(), m = read();
	C[0][0] = C[1][0] = C[1][1] = 1;
	for(rint i = 2; i <= m; i++){
		C[i][0] = 1;
		for(rint j = 1; j <= i; j++) C[i][j] = add(C[i - 1][j], C[i - 1][j - 1]);
	}
	f[0][0] = 1;
 	for(rint i = 1; i <= 19; i++) for(rint j = 0; j <= n; j++){
		for(rint k = 0; k <= min(m, j / (1 << (i - 1))); k += 2){
			rint t = (1 << (i - 1));
			f[i][j] = add(f[i][j], 1ll * f[i - 1][j - k * t] * C[m][k] % P);
		}
	}
	printf("%d", f[19][n]);
	return 0;
}
