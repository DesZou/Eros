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

const int MAXN = 210, MOD = 1000000007;

LL f[MAXN][MAXN];

int n;

int main()
{
	freopen("road.in", "r", stdin);
	freopen("road.ans", "w", stdout);
	
	in(n);

	memset(f, 0x3f, sizeof f);
	
	FOR(i, 1, n) {
		int x, y;
		in(x); in(y);
		f[i][x] = y;
	}

	FOR(i, 1, n) f[i][i] = 0;

	FOR(k, 1, n) FOR(i, 1, n) FOR(j, 1, n)
		chkmin(f[i][j], f[i][k] + f[k][j]);

	LL ans = 0;
	
	FOR(i, 1, n) FOR(j, 1, n) {
		if (f[i][j] == 0x3f3f3f3f3f3f3f3fLL) ans = (ans - 1 + MOD) % MOD;
		else ans = (ans + f[i][j]) % MOD;
	}

	printf("%lld\n", ans);
	
	return 0;
}
