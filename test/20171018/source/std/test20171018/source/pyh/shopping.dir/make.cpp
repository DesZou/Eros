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

int main()
{
	int seed; in(seed); srand(seed);

	freopen("shopping.in", "w", stdout);

	int n = 100000, m = 100000;

	printf("%d %d\n", n, m);

	FOR(i, 1, n) {
		printf("%d %d\n", rand() % 1000000000 + 1, rand() % 1000000000 + 1);
	}

	FOR(i, 1, m) {
		int tp = rand() % 2 + 1;
		printf("%d ", tp);
		if (tp == 1) {
			int pos = rand() % n + 1;
			printf("%d %d %d\n", pos, rand() % 10 + 1, rand() % 10 + 1);
		}
		else printf("%d\n", rand() % 1000000000 + 1);
	}

	putchar(10);
	
	return 0;
}
