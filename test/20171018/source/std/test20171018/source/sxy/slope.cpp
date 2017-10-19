//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
const int maxn=5e5+10;
int n,x[maxn],y[maxn],p[maxn];
double ans=-1e9;

int aa,ff;char cc;
int read() {
	aa=0;cc=getchar();ff=1;
	while(cc<'0'||cc>'9') {
		if(cc=='-') ff=-1;
		cc=getchar();
	}
	while(cc>='0'&&cc<='9') aa=aa*10+cc-'0',cc=getchar();
	return aa*ff;
}

bool cmp(int a,int b) {
	return x[a]<x[b];
}

double lv(int a,int b) {
	return (double)b*1.0/a;
}

int main() {
	freopen("slope.in","r",stdin);
	freopen("slope.out","w",stdout);
	n=read();int a,b;
	for(int i=1;i<=n;++i) {
		x[i]=read();
		y[i]=read();
		p[i]=i;
	}
	sort(p+1,p+n+1,cmp);
	for(int i=2;i<=n;++i) {
		a=p[i-1];b=p[i];
		ans=max(ans,lv(x[b]-x[a],y[b]-y[a]));
	}
	printf("%.3lf",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}

