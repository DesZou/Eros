#include <iostream>
#include <cassert>
#include <algorithm>
#include <cstdio>

const int Inf = -1u >> 2;
const int N = 2e5 + 5;

int n, m, L, pivot = -1;
int a[N], l[N];
int post[N], prev[N];

struct Data { int v, p, place, id; } tr[N << 2];
struct Tag { int dv, dp; } tag[N << 2];

struct Walker { int s, b, tar, dis, id; } w[N];

bool operator<(const Walker &a, const Walker &b) {
	return (a.s == b.s)? (a.b < b.b) : (a.s < b.s);
}

bool operator<(const Data &a, const Data &b) {
	return (a.v == b.v)? (a.id < b.id) : (a.v < b.v);
}

void pushdown(int i) {
	if (tag[i].dv || tag[i].dp) {
	 	 tr[i << 1].v      += tag[i].dv;
		tag[i << 1].dv     += tag[i].dv;
		 tr[i << 1 | 1].v  += tag[i].dv;
		tag[i << 1 | 1].dv += tag[i].dv;
		if (tag[i].dp) {
			tr[i << 1].p       = tag[i].dp;
			tr[i << 1 | 1].p   = tag[i].dp;
			tag[i << 1].dp     = tag[i].dp;
			tag[i << 1 | 1].dp = tag[i].dp;
		}
		tag[i].dv = tag[i].dp = 0;
	}
}

void pushup(int i) {
	tr[i] = std::min(tr[i << 1], tr[i << 1 | 1]);
}

void block(int i, int l, int r, int pos) {
	if (l == r) {
		tr[i].v = Inf;
	} else {
		pushdown(i);
		int mid = (l + r) >> 1;
		if (pos <= mid) block(i << 1, l, mid, pos);
		else block(i << 1 | 1, mid + 1, r, pos);
		pushup(i);
	}
}

void modify(int i, int l, int r, int s, int t, Tag key) {
	// if (i == 1) std::cerr << s << " " << t << std::endl;
	if (l >= s && r <= t) {
		tr[i].v   += key.dv;
		tag[i].dv += key.dv;
		if (key.dp) {
			tr[i].p    = key.dp;
			tag[i].dp  = key.dp;
		}
	} else {
		pushdown(i);
		int mid = (l + r) >> 1;
		if (mid >= s) modify(i << 1, l, mid, s, t, key);
		if (t > mid) modify(i << 1 | 1, mid + 1, r, s, t, key);
		pushup(i);
	}
}

void build(int i, int l, int r) {
	if (l == r) {
		tr[i] = (Data){ w[l].dis, w[l].tar, l, w[l].id };
	} else {
		int mid = (l + r) >> 1;
		build(i << 1, l, mid);
		build(i << 1 | 1, mid + 1, r);
		pushup(i);
	}
}

void update(int x, int y, int s, Tag key) {
	if (s == 0) {
		int lft = std::lower_bound(w + 1, w + pivot, (Walker){ s, x, 0, 0, 0 }) - w;
		int rgt = std::upper_bound(w + 1, w + pivot, (Walker){ s, y, 0, 0, 0 }) - w - 1;
		if (lft <= rgt) modify(1, 1, n, lft, rgt, key);
	} else {
		int lft = std::lower_bound(w + pivot, w + 1 + n, (Walker){ s, x, 0, 0, 0 }) - w;
		int rgt = std::upper_bound(w + pivot, w + 1 + n, (Walker){ s, y, 0, 0, 0 }) - w - 1;
		if (lft <= rgt) modify(1, 1, n, lft, rgt, key);
	}
}

int main() {
	std::ios::sync_with_stdio(false);

	std::cin >> n >> m >> L;

	for (int i = 2; i <= m; ++i) std::cin >> a[i];
	for (int i = 1; i <= m; ++i) std::cin >> l[i];

	for (int i = 1; i <= n; ++i) {
		std::cin >> w[i].s >> w[i].b;

		w[i].id = i;

		w[i].tar = (w[i].s == 0)? 
			std::lower_bound(a + 1, a + 1 + m, w[i].b) - a:
			std::upper_bound(a + 1, a + 1 + m, w[i].b) - a - 1;
		if (w[i].tar == m + 1) w[i].tar = 1;

		w[i].dis = (w[i].s == 0)?
			(a[w[i].tar] - w[i].b + L) % L:
			w[i].b - a[w[i].tar];
	}

	std::sort(w + 1, w + 1 + n);

	for (int i = 1; i <= n; ++i) if (w[i].s == 1) {
		pivot = i;
		break;		
	}

	if (pivot == -1) pivot = n + 1;

	build(1, 1, n);

	for (int i = 1; i <= m; ++i) {
		prev[i] = i - 1;
		post[i] = i + 1;
	}
	prev[1] = m;
	post[m] = 1;

	int cntq = m;
	long long ans = 0;

	for (int i = 1; i <= n; ++i) {
		int now = tr[1].place, rmv = tr[1].p;

		ans ^= (1ll * tr[1].id * rmv);

		block(1, 1, n, now);

		// std::cerr << w[now].id << " -> " << rmv << std::endl;;

		if ((--l[rmv]) == 0) {
			if ((--cntq) == 0) break;

			int ldis = (a[post[rmv]] - a[rmv] + L) % L,
				rdis = (a[rmv] - a[prev[rmv]] + L) % L;

			int x1 = (a[prev[rmv]] + 1) % L;
			int y1 = a[rmv];

			if (x1 > y1) {
				update(0, y1, 0, (Tag){ ldis, post[rmv] });
				update(x1, L - 1, 0, (Tag){ ldis, post[rmv] });
			} else {
				update(x1, y1, 0, (Tag){ ldis, post[rmv] });
			}


			int x2 = a[rmv];
			int y2 = (a[post[rmv]] - 1 + L) % L;

			if (x2 > y2) {
				update(0, y2, 1, (Tag){ rdis, prev[rmv]});
				update(x2, L - 1, 1, (Tag){ rdis, prev[rmv] });
			} else {
				update(x2, y2, 1, (Tag){ rdis, prev[rmv] });
			}

			// std::cerr << x1 << "," << y1 << std::endl;
			// std::cerr << x2 << "," << y2 << std::endl;

			post[prev[rmv]] = post[rmv];
			prev[post[rmv]] = prev[rmv];
		}
	}

	std::cout << ans << std::endl;

	return 0;
}
