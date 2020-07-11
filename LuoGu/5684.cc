#include <iostream>
#include <iterator>
#include <algorithm>
#include <cstdio>

const long long Mod = 1e9 + 7;
const int C = 26;
const int N = 2e3 + 5;

int n;
int c[C];
long long inv[N], fac[N];

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n;

	char x;
	for (int i = 1; i <= n; ++i) {
		std::cin >> x;
		++c[x - 'a'];
	}

	fac[0] = inv[1] = inv[0] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = (fac[i - 1] * i) % Mod;
	for (int i = 2; i <= n; ++i) inv[i] = ((Mod - Mod / i) * inv[Mod % i]) % Mod;
	for (int i = 2; i <= n; ++i) inv[i] = (inv[i] * inv[i - 1]) % Mod;

	int flag = 0;

	for (int i = 0; i < C; ++i) {
		flag += c[i] & 1;
	}

	if (flag - (n & 1)) {
		std::cout << fac[n] << std::endl;
		return 0;
	}

	long long ans = fac[n >> 1];

	for (int i = 0; i < C; ++i)
		ans = (((ans * fac[c[i]]) % Mod) * inv[c[i] >> 1]) % Mod;

	std::cout << (fac[n] - ans + Mod) % Mod << std::endl;

	return 0;
}
