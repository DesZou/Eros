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

const int MAXN = 100010;

int n, m;
int w[MAXN], p[MAXN];

int main()
{
	freopen("shopping.in", "r", stdin);
	freopen("shopping.ans", "w", stdout);
	
	in(n); in(m);

	FOR(i, 1, n) in(w[i]), in(p[i]);

	FOR(i, 1, m) {
		int tp; in(tp);
		if (tp == 1) {
			int pos; in(pos);
			in(w[pos]); in(p[pos]);
		}
		else {
			int k; in(k);
			LL ans = 0;
			while (true) {
				int pos = -1;
				FOR(j, 1, n) {
					if (k >= p[j]) {
						if (pos == -1 ||
							w[pos] < w[j] || (w[pos] == w[j] && p[pos] > p[j]))
						{
							pos = j;
						}
					}
				}
				if (pos == -1) break;
				ans += 1ll * (k / p[pos]) * w[pos];
				k %= p[pos];
			}
			printf("%lld\n", ans);
		}
	}
	
	return 0;
}
