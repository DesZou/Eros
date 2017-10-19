#include <bits/stdc++.h>

typedef long long LL;

#define FOR(i, a, b) for (int i = (a), i##_END_ = (b); i <= i##_END_; i++)
#define DNF(i, a, b) for (int i = (a), i##_END_ = (b); i >= i##_END_; i--)

template <typename Tp> void in(Tp &x) {
	char ch = getchar(), f = 1; x = 0;
	while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
	if (ch == '-') ch = getchar(), f = -1;
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
	x *= f;
}

template <typename Tp> Tp Max(const Tp &x, const Tp &y) {return x > y ? x : y;}
template <typename Tp> Tp Min(const Tp &x, const Tp &y) {return x < y ? x : y;}
template <typename Tp> bool chkmax(Tp &x, Tp y) {return x >= y ? 0 : (x=y, 1);}
template <typename Tp> bool chkmin(Tp &x, Tp y) {return x <= y ? 0 : (x=y, 1);}

const int MAXN = 210;

LL n; LL p;
LL num[MAXN];

LL mul(LL x, LL y)
{
	x %= p;
	LL ret = 0;
	while (y) {
		if (y & 1) ret = (ret + x) % p;
		x = (x + x) % p;
		y >>= 1;
	}
	return ret;
}

int main()
{
	freopen("sum.in", "r", stdin);
	freopen("sum.ans", "w", stdout);

	in(n); in(p);
	FOR(i, 1, n) in(num[i]);

	LL ans = 0;

	FOR(i, 1, n) FOR(j, i, n) {
		LL mu = 1;
		FOR(k, i, j) mu = mul(mu, num[k]);
		ans = (ans + mu) % p;
	}

	printf("%lld\n", ans);
	
	return 0;
}
