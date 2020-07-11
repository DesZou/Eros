#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iomanip>

template<class T> bool chkmin(T &a, const T b) { return a > b? a = b, 1 : 0; }

const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };
const double Eps = 1e-6;

double x[3], y[3], r[3], g[3];

double f(double ax, double ay) {
	for (int i = 0; i < 3; ++i)
		g[i] = std::hypot(x[i] - ax, y[i] - ay) / r[i];

	double ret = 0;

	for (int i = 0; i < 3; ++i)
		ret += pow(g[i] - g[(i + 1) % 3], 2);

	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);

	double dt = 1, ax = 0, ay = 0;

	for (int i = 0; i < 3; ++i) {
		std::cin >> x[i] >> y[i] >> r[i];
		ax += x[i];
		ay += y[i];
	}

	ax /= 3;
	ay /= 3;

	while (dt > Eps) {
		int flag = -1;

		double ths = f(ax, ay);

		for (int i = 0; i < 4; ++i)
			if (chkmin(ths, f(ax + dx[i] * dt, ay + dy[i] * dt)))
				flag = i;

		if (flag == -1) dt /= 2;
		else { ax += dx[flag] * dt; ay += dy[flag] * dt; }
	}

	if (f(ax, ay) < Eps)
		std::cout << std::fixed << std::setprecision(5)
			<< ax << ' ' << ay << std::endl;

	return 0;
}
