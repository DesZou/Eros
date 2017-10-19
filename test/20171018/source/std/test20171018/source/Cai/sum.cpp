#include <cstdio>
#include <cstring>
#include <algorithm>

#define DEBUG(args...) fprintf(stderr, args)

#define FOR(i, l, r) for(int i=(l), i##_end=(r); i<=i##_end; ++i)
#define REP(i, l, r) for(int i=(l), i##_end=(r); i< i##_end; ++i)
#define DFR(i, l, r) for(int i=(l), i##_end=(r); i>=i##_end; --i)
#define DRP(i, l, r) for(int i=(l), i##_end=(r); i> i##_end; --i)

typedef long long LL;
typedef unsigned long long ULL;

template<class T>T Min(const T &a, const T &b) {return a < b ? a : b;}
template<class T>T Max(const T &a, const T &b) {return a > b ? a : b;}
template<class T>bool Chkmin(T &a, const T &b) {return a > b ? a=b, 1 : 0;}
template<class T>bool Chkmax(T &a, const T &b) {return a < b ? a=b, 1 : 0;}

namespace FI {
	const int SIZE = 1 << 15 | 1;
	char buf[SIZE], *front, *back;
	void NextChar(char &c) {
		if(front == back) back = (front=buf) + fread(buf, 1, SIZE, stdin);
		c = front==back ? (char)EOF : *front++;
	}
	template<class T> void NextInt(T &x) {
		char c;
		for(NextChar(c); c>'9'||c<'0'; NextChar(c)) ;
		for(x=0; c>='0'&&c<='9'; NextChar(c)) x = (x<<3)+(x<<1)+c-'0';
	}
}

const int SN = 100000 + 47;

ULL ans, sum, mod;
int n;

ULL Mul(ULL, ULL);
ULL F(ULL);

int main() {

	freopen("sum.in", "r", stdin);
	freopen("sum.out", "w", stdout);

	int x;
	
	FI::NextInt(n), FI::NextInt(mod);
	FOR(i, 1, n)
		FI::NextInt(x), x %= mod, sum = F(Mul(sum, x) + x), ans = F(ans + sum);

	printf("%llu\n", ans);

	return 0;

}

ULL Mul(ULL x, ULL y) {
	ULL ret = 0;
	while(y) {
		if(y & 1) ret = F(ret + x);
		x = F(x << 1), y >>= 1;
	}
	return ret;
}

ULL F(ULL x) {
	return x >= mod ? x - mod : x;
}
