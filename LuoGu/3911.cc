/**
 *	luogu 3911
 *
 *	mobius inversion
 *
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

const int N = 3e5 + 5;

int cnt[N];
int p[N];
long long mu[N];
long long f[N];
bool notp[N];

int n, m;

void sieve() {
	mu[1] = 1;
	for (int i = 2; i <= m; ++i) {
		if (!notp[i]) { p[++*p] = i; mu[i] = -1; }
		for (int j = 1, k = i * 2; j <= *p && k <= m; k = i * p[++j]) {
			notp[k] = true;
			if (i % p[j] == 0) {
				mu[k] = 0;
				break;
			}
			mu[k] = -mu[i];
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	
	std::cin >> n;

	for (int i = 1, a; i <= n; ++i) {
		std::cin >> a;
		++cnt[a];
		m = std::max(m, a);
	}

	sieve();

	for (int i = 1; i <= m; ++i)
		for (int j = i; j <= m; j += i)
			f[j] += i * mu[i];

	long long ans = 0;

	for (int i = 1; i <= m; ++i) {
		long long tmp = 0;
		for (int j = 1; j <= m / i; ++j) {
			tmp += cnt[i * j] * j;
		}
		ans += i * f[i] * tmp * tmp;
	}

	std::cout << ans << std::endl;

	return 0;
}
