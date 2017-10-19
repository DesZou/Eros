#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int sm = 1e5 + 19;

int n;
LL p,a[sm];
LL c,ans;

LL M(LL x,LL y) {
	if(x > p) x %= p;
	if(y > p) y %= p;
	return (x+y)%p;
}

LL Mul(LL a,LL b) {
	LL ret = 0;
	while(b) {
		if(b & 1) ret = M(ret,a);
		a = M(a,a);
		b >>= 1;
	}
	return ret;
}

int main() {
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);

	scanf("%d%lld",&n,&p);
	for(int i = 1; i <= n; ++i)
		scanf("%lld",&a[i]);
	
	for(int i = n; i >= 1; --i) {
		c = Mul(c+1,a[i]);
		ans = M(ans,c);
	}
	
	printf("%lld\n",ans);
	
	return 0;
}
