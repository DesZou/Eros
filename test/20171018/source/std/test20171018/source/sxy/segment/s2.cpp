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
double tot[2][maxn],sum[2][maxn];

double aa;char cc;
double read() {
	aa=0;cc=getchar();
	while(cc<'0'||cc>'9') cc=getchar();
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa;
}

double sz1[maxn];
void add(int pos,double x,double*sz) {
	while(pos<=n) {
		sz[pos]+=x;
		pos+=(pos&-pos);
	}
}

double q(int pos,double* sz) {
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
		add(l,1,tot[op>>1]);add(r+1,-1,tot[op>>1]);
		add(l,x,sum[op>>1]);add(r+1,-x,sum[op>>1]);
	}
	double a,xx,nowans,now,tot0,tot1,sum0,sum1;
	for(int i=1;i<=n;++i) {
		tot0=q(i,tot[0]);tot1=q(i,tot[1]);
		sum0=q(i,sum[0]);sum1=q(i,sum[1]);
		if(!tot0&&!tot1) nowans=d[i];
		else if(tot0&&!tot1) nowans=(double)d[i]+sum0;
		else if(!tot0&&tot1) nowans=(double)sum1*1.0/tot1;
		else {
			a=(double)sum0*1.0/tot0;
			nowans=(double)sum1*1.0/tot1;
			now=1.0;
			for(int j=1;j<=tot0;++j) {
				xx=(double)a*(tot0-j+1)*1.0/(tot0+tot1-j+1)*now;
				now*=(double)(tot0-j+1)*1.0/(tot0+tot1-j+1);
				nowans+=xx;
			}
		}
		add(i,nowans,sz1);
	}
	for(int i=1;i<=k;++i) {
		l=read();r=read();
		printf("%.3lf\n",q(r,sz1)-q(l-1,sz1));
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
