//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=100+10,maxs=15,INF=0x3f3f3f3f;
int n,m,sz,len,dis[maxn][maxn][maxs],ans[maxn][maxn],g[maxn][maxn],q;

int aa;char cc;
int read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

int f(int x){int rs=0;while(x){x>>=1;rs++;} return rs;}

int main() {
	freopen("graph.in","r",stdin);
	freopen("graph.out","w",stdout);
	n=read();m=read();len=read();
	int x,y,z; sz=f(len);
	memset(dis,0x3f3f3f3f,sizeof(dis));
	for(int i=1;i<=m;++i) {
		x=read();y=read();z=read();
		dis[x][y][0]=dis[y][x][0]=min(dis[x][y][0],z);
	}
	for(int p=1;p<=sz;++p) {
		for(int i=1;i<=n;++i) for(int j=i;j<=n;++j) for(int k=1;k<=n;++k)
		dis[i][j][p]=dis[j][i][p]=min(dis[i][j][p],dis[i][k][p-1]+dis[k][j][p-1]);
	}
	memset(ans,0x3f3f3f3f,sizeof(ans));
	for(int i=1;i<=n;++i) ans[i][i]=0;
	for(int p=sz;~p&&len;--p) if(len>=(1<<p)){
		len-=(1<<p); memset(g,0x3f3f3f3f,sizeof(g));
		for(int i=1;i<=n;++i) for(int j=i;j<=n;++j) 
		for(int k=1;k<=n;++k) g[i][j]=g[j][i]=min(g[i][j],ans[i][k]+dis[k][j][p]);
		memcpy(ans,g,sizeof(g));
	}
	q=read();
	for(int i=1;i<=q;++i) {
		x=read();y=read();
		printf("%d\n",ans[x][y]>=INF? -1:ans[x][y]);
	}
	fclose(stdin);fclose(stdout);
	return 0;
}

