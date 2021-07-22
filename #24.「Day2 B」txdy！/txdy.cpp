#include<bits/stdc++.h>
using namespace std;
const int CN = 1e6 + 60;
const char tmp[10] = "txdy";
int n, len, to[CN][50]; char s[CN], t[CN];
bool ck(){
	if(len <= 0) return 0;
	int p = 0;
	for(int i = 0; t[i]; i++){
		if(t[i] != s[p] || p > len) return 0;
		if(t[i + 1]){
		    if(!to[p][t[i + 1] - 'a']) return 0;
		    p = to[p][t[i + 1] - 'a'];
	    }
	}
	return 1;
}
int main()
{
	ios :: sync_with_stdio(false);
	cin >> s; len = strlen(s) - 2;
	for(int i = 3; i + 1; i--){
		while(len >= 0 && s[len] != tmp[i]) len--; 
		len -= 2;
	}
	for(int i = len - 2; i >= 0; i--){
		for(int j = 0; j < 26; j++) to[i][j] = to[i + 1][j];
		to[i][s[i + 2] - 'a'] = i + 2;
	}
	cin >> n;
	while(n--) {cin >> t; putchar("01"[ck()]);}
	return 0;
}
