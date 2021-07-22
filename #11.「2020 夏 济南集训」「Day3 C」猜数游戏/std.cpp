#include"guess.h"
//#include "..\..\data\guess\guess.h"
int bel[1010];
vector<int> guess(int testid,int n,int k){
	vector<int> chk,ans;
	int i,j,q = 1 << k - 1,lft = n;
	while(lft > q){
		int nw = q;
		for(i = 0;i < n;++i) if(bel[i] != -1){
			if(nw == q) nw = 0;
			else ++nw;
			bel[i] = nw;
		}
		bool q1 = 0;int q2 = 0;
		for(i = 1;i <= k;++i){
			chk.clear();
			for(j = 0;j < n;++j) if(bel[j] == q) chk.push_back(j);
			if(query(chk)){
				q1 = 1;break;
			}
		}
		if(!q1){
			for(j = 0;j < n;++j) if(bel[j] == q) bel[j] = -1,--lft;
		}
		else{
			for(i = 1;i < q;i <<= 1){
				chk.clear();
				for(j = 0;j < n;++j) if(bel[j] != -1 && (bel[j] & i)) chk.push_back(j);
				if(!query(chk)) q2 += i; 
			}
			for(j = 0;j < n;++j) if(bel[j] == q2) bel[j] = -1,--lft;
		}
	}
	for(i = 0;i < n;++i) if(bel[i] != -1) ans.push_back(i);
	return ans;
}
