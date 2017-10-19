//by Saramanda
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define For(i,_beg,_end) for(int i=(_beg),i##end=(_end);i<=i##end;++i)
#define Rep(i,_beg,_end) for(int i=(_beg),i##end=(_end);i>=i##end;--i)

template<typename T>T Max(const T &x,const T &y){return x<y?y:x;}
template<typename T>T Min(const T &x,const T &y){return x<y?x:y;}
template<typename T>int chkmax(T &x,const T &y){return x<y?(x=y,1):0;}
template<typename T>int chkmin(T &x,const T &y){return x>y?(x=y,1):0;}
template<typename T>void read(T &x){
	T f=1;char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;
	for(x=0;ch>='0'&&ch<='9';ch=getchar())x=x*10+ch-'0';
	x*=f;
}

typedef long long LL;
const int maxn=100010;
int n,a[maxn];
LL p,ans,tot;

inline LL f(const LL &x){return x>=p?x-p:x;}
LL mul(LL x,LL y){
	LL res=0;
	for(;y;y>>=1,x=f(x+x)) if(y&1)res=f(res+x);
	return res;
}

int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	read(n);read(p);
	For(i,1,n){
		read(a[i]);a[i]%=p;
		tot=f(mul(tot,a[i])+a[i]);
		ans=f(ans+tot);
	}
	printf("%lld\n",ans);
	return 0;
}
