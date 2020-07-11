/**
 *	luogu 3935
 *
 *	block by divide
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>

const long long P = 998244353;

long long l, r;

template<class T> T mul(T a, T b) {
	return (((unsigned long long)a * b - (a / P * b) * P) + P) % P;
}

long long f(long long n) {
	long long ret = 0;
	for (long long i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		(ret += mul(n / i, j - i + 1)) %= P;
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> l >> r;

	std::cout << (f(r) - f(l - 1) + P) % P << std::endl;

	return 0;
}
