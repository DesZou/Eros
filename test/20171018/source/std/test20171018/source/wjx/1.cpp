//Twenty
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<queue>
using namespace std;
typedef long long LL;
const int maxn=1e5+5;
LL n,p,a[maxn],f[maxn],ans;

void read(LL &x) {
    LL ret=0,f=1; char ch=getchar();
    while(ch!='-'&&(ch<'0'||ch>'9')) ch=getchar();
    if(ch=='-') f=-1,ch=getchar();
    for(;ch>='0'&&ch<='9';ch=getchar()) ret=ret*10+ch-'0';
    x=ret;
}

LL ksc(LL a,LL b) {
    a%=p; b%=p;
    LL base=a,res=0;
    while(b) {
    	if(b&1) (res+=base)%=p;
    	(base+=base)%=p;
    	b>>=1;
	}
	return res;
}

int main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	read(n); read(p);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=n;i>=1;i--) {
	    f[i]=(ksc(f[i+1],a[i])+a[i])%p;
	    (ans+=f[i])%=p;
	}
	printf("%lld\n",ans);
	return 0;
}
