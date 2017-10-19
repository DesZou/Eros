//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
const int maxn=500+10;
const ll INF=0x7f7f7f7f7f7f7f7f,I2=0x3f3f3f3f;
int n,m,dis[maxn][maxn],p[maxn],d[maxn];
ll ans[maxn][maxn];

ll aa;char cc;
inline ll read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

inline bool cmp(int a,int b) {
	return d[a]<d[b];
}

int main() {
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	n=read();m=read();
	int x,y,z;
	memset(dis,0x3f3f3f3f,sizeof(dis));
	memset(ans,0x7f,sizeof(ans));
	for(int i=1;i<=n;++i) {
		dis[i][i]=ans[i][i]=0;
		p[i]=i; d[i]=read();
	}
	for(int i=1;i<=m;++i) {
		x=read();y=read();z=read();
		dis[x][y]=dis[y][x]=min(dis[x][y],z);
	}
	sort(p+1,p+n+1,cmp);
	for(register int k=1;k<=n;++k) {
		x=p[k]; y=d[x];
		for(register int i=1;i<n;++i) for(register int j=i+1;j<=n;++j) {
			dis[i][j]=dis[j][i]=min(dis[i][j],max(dis[i][x],dis[x][j]));
			if(d[i]<=d[x]&&d[j]<=d[x]&&dis[i][j]<I2)
				ans[i][j]=ans[j][i]=min(ans[i][j],(ll)dis[i][j]*y);
		}
	}
	for(register int i=1;i<=n;++i) {
		for(register int j=1;j<=n;++j) 
			if(ans[i][j]<INF) printf("%lld ",ans[i][j]); 
			else printf("-1 ");
		printf("\n");
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
/*
4 2
1 2 3 4
1 3 1
1 2 1
*/
