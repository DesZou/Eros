#include <cstdio>
#include <cstring>
#include <algorithm>

template <typename Tp>Tp Max(const Tp &a, const Tp &b) {return a > b ? a : b;}
template <typename Tp>Tp Min(const Tp &a, const Tp &b) {return a < b ? a : b;}

template <typename Tp>void Read(Tp &x) {
	Tp in = 0, f = 1; char ch = getchar();
	while(ch<'0' || ch>'9') {if(ch=='-') f = -1; ch = getchar();}
	while(ch>='0' && ch<='9') {in = in*10+ch-'0'; ch = getchar();}
	x = in*f;
}

typedef long long LL;

const int SN = 100000 + 10;

LL a[SN], n, MOD, sum, ans;

LL ksc(LL a, LL b) {
	LL ans = 0, B = a % MOD;
	b %= MOD;
	while(b) {
		if(b & 1) ans = (ans + B)%MOD;
		B = (B + B)%MOD;
		b >>= 1;
	}
	return ans;
}

int main() {
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	
	Read(n), Read(MOD);

	for(int i = 1; i <= n; i++) Read(a[i]);

	sum = 0;
	
	for(int i = 1; i <= n; i++) {
		sum = ksc((sum+1), a[i]);
		ans = (ans + sum)%MOD;
	}

	printf("%lld\n", ans);

	return 0;
}
