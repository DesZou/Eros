//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
#define ll long long
const int maxn=100000+10;
int n,m,k,d[maxn];
ll tot[2][maxn],sum[2][maxn];

ll aa;char cc;
ll read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

double sz[maxn];
void add(int pos,double x) {
	while(pos<=n) {
		sz[pos]+=x;
		pos+=(pos&-pos);
	}
}

double q(int pos) {
	double rs=0;
	while(pos) {
		rs+=sz[pos];
		pos-=(pos&-pos);
	}
	return rs;
}

int main() {
	freopen("segment.in","r",stdin);
	freopen("segment.out","w",stdout);
	n=read();m=read();k=read();
	ll op,l,r,x;
	for(int i=1;i<=n;++i) d[i]=read();
	for(int i=1;i<=m;++i) {
		op=read();l=read();r=read();x=read();
		for(int j=l;j<=r;++j) tot[op>>1][j]++,sum[op>>1][j]+=x;
	}
	double a,xx,nowans,now;
	for(int i=1;i<=n;++i) {
		if(!tot[0][i]&&!tot[1][i]) nowans=d[i];
		else if(tot[0][i]&&!tot[1][i]) nowans=(double)d[i]+sum[0][i];
		else if(!tot[0][i]&&tot[1][i]) nowans=(double)sum[1][i]*1.0/tot[1][i];
		else {
			a=(double)sum[0][i]*1.0/tot[0][i];
			nowans=(double)sum[1][i]*1.0/tot[1][i];
			now=1.0;
			for(int j=1;j<=tot[0][i];++j) {
				xx=(double)a*(tot[0][i]-j+1)*1.0/(tot[0][i]+tot[1][i]-j+1)*now;
				now*=(double)(tot[0][i]-j+1)*1.0/(tot[0][i]+tot[1][i]-j+1);
				nowans+=xx;
			}
		}
		add(i,nowans);
	}
	for(int i=1;i<=k;++i) {
		l=read();r=read();
		printf("%.3lf\n",q(r)-q(l-1));
	}
	fclose(stdin);fclose(stdout);
	return 0;
}
/*
5 4 8
2 3 3 3 3
1 1 3 2
1 3 5 1
2 2 4 1
2 1 3 4
1 1
2 2
3 3
4 4
5 5
1 3
2 5
1 5
*/
