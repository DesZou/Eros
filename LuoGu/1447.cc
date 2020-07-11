/**
 * luogu 1447
 *
 * mobius inversion
 *
 */
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

const int N = 1e5 + 5;

int n, m;
int prime[N];
bool notp[N];
long long mu[N];

void sieve() {
	mu[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!notp[i]) { prime[++*prime] = i; mu[i] = -1; }
		for (int j = 1, k = 2 * i;
			 j <= *prime && k <= n;
			 k = prime[++j] * i) {
			notp[k] = true;
			if (!(i % prime[j])) break;
			mu[k] = -mu[i];
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n >> m;

	if (n > m) std::swap(n, m);

	sieve();

	long long ans = 0;

	for (int d = 1; d <= n; ++d)
		for (int i = 1; i <= n / d; ++i)
			ans += mu[i] * (n / (d * i)) * (m / (d * i)) * d;

	std::cout << ans * 2 - (long long)n * m << std::endl;

	return 0;
}
