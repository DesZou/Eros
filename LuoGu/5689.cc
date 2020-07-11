#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>

const long long P = 1e9 + 7;
const int N = 3e5 + 5;

int n, q;
int fa[N];
long long f[N], s[N];
long long inv[N], fac[N];

int find(int x) {
	return x == fa[x]? x : fa[x] = find(fa[x]);
}

long long C(int n, int m) {
	return ((fac[n] * inv[m]) % P * inv[n - m]) % P;
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n >> q;

	for (int i = 0; i < n; ++i) fa[i] = i;
	for (int i = 0; i < n; ++i) f[i] = s[i] = 1;
	
	fac[0] = inv[0] = inv[1] = 1;
	for (int i = 1; i <= n; ++i) fac[i] = (fac[i - 1] * i) % P;
	for (int i = 2; i <= n; ++i) inv[i] = ((P - P / i) * inv[P % i]) % P;
	for (int i = 2; i <= n; ++i) inv[i] = (inv[i - 1] * inv[i]) % P;

	long long ans = 0;

	for (int opt, x, y; q --> 0;) {
		std::cin >> opt;
		if (opt == 1) {
			std::cin >> x >> y;
			x = find((ans + x) % n);
			y = find((ans + y) % n);
			s[y] = s[x] + s[y];
			f[y] = (((f[y] * f[x]) % P) * C(s[y] - 1, s[x])) % P;
			fa[x] = y;
		} else {
			std::cin >> x;
			std::cout << (ans = f[find((ans + x) % n)]) << std::endl;
		}
	}
	
	return 0;
}
