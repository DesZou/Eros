#include <cstdio>
#include <cstring>
#include <algorithm>
#define last last2
#define MOD 1000000007

using namespace std;

int f[10][100000],powd[10],ans[10],all;
char s[10][10];

void dp(int sz,int n) {
  int msize=1;
  for(int i=1;i<=n-sz+1;i++) msize*=sz;
  powd[0]=1;
  for(int i=1;i<=n;i++) powd[i]=powd[i-1]*sz;
  for(int i=0;i<=n;i++)
    for(int j=0;j<msize;j++) f[i][j]=0;
  f[0][0]=1;
  for(int i=0;i<n;i++)
    for(int j=0;j<msize;j++)
      if (f[i][j]) 
      for(int cur=0;cur<(1<<n);cur++) {
      	bool in[10];
      	memset(in,0,sizeof(in));
      	bool ok=1;
      	for(int k=0;k<n;k++)
      	  if ((cur&(1<<k))&&(s[i+1][k]=='*')) {
      	  	  ok=0;break;
			}
		  else if (!(cur&(1<<k))) {
		  	for(int l=max(0,k-sz+1);l<=k;l++) in[l]=1;
		  }
		if (!ok) continue;
		int st=0,lst=j,last=0;
		for(int k=0;k<=n-sz;k++) {
			last=lst%sz;
			if (in[k]) st=st;
			else if (last==sz-1) {
				ok=0;break;
			}
			else st+=(last+1)*powd[k];
			lst/=sz;
		}
		if (!ok) continue;
		f[i+1][st]=(f[i+1][st]+f[i][j])%MOD;
	  }
  ans[sz]=0;
  for(int i=0;i<msize;i++) ans[sz]=(ans[sz]+f[n][i])%MOD;
  ans[sz]=(all-ans[sz]+MOD)%MOD;
}

int main() {
  freopen("1.in","r",stdin);
  freopen("1.out","w",stdout);
  	int n;
  	scanf("%d",&n);
  	for(int i=1;i<=n;i++) scanf("%s",s[i]);
  	all=1;
  	for(int i=1;i<=n;i++)
  	  for(int j=0;j<n;j++)
  	    if (s[i][j]!='*') all=all*2%MOD;
  	ans[0]=all;ans[n+1]=0;
  	for(int i=1;i<=n;i++) 
	  dp(i,n);
  	for(int i=0;i<=n;i++) printf("%d\n",(ans[i]-ans[i+1]+MOD)%MOD);
  return 0;
}
