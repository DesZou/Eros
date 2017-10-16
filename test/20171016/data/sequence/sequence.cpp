#include <bits/stdc++.h>

typedef long long ll;

const int MAXN = 200000 + 5;

namespace SegTree {
	ll sum[MAXN << 2], tag[MAXN << 2];
	
	void down(int k, int l, int mid, int r) {
		if (tag[k]) {
			sum[k << 1] += tag[k] * (mid - l + 1);
			sum[k << 1 | 1] += tag[k] * (r - mid);
			tag[k << 1] += tag[k];
			tag[k << 1 | 1] += tag[k];
			tag[k] = 0;
		}
	}
	
	void modify(int k, int l, int r, int L, int R, ll val) {
		if (L <= l && r <= R) {
			sum[k] += val * (r - l + 1);
			tag[k] += val;
			return;
		}
		int mid = (l + r) >> 1;
		down(k, l, mid, r);
		if (L <= mid) modify(k << 1, l, mid, L, R, val);
		if (mid < R) modify(k << 1 | 1, mid + 1, r, L, R, val);
		sum[k] = sum[k << 1] + sum[k << 1 | 1];
	}
	
	ll query(int k, int l, int r, int L, int R) {
		if (L <= l && r <= R) return sum[k];
		int mid = (l + r) >> 1;
		down(k, l, mid, r);
		ll res = 0;
		if (L <= mid) res += query(k << 1, l, mid, L, R);
		if (mid < R) res += query(k << 1 | 1, mid + 1, r, L, R);
		return res;
	}
}

int n, m, k, q;
int a[MAXN];

struct Query {
	int l, r, id;
	
	void scan(int ID) {
		scanf("%d%d", &l, &r); id = ID;
	}
	
	bool operator < (const Query &rhs) const {
		return r < rhs.r;
	}
} qry[MAXN];

ll ans[MAXN];

std::string fileName("sequence");

int main(int argc, char *argv[]) {
	assert(argc >= 1);
	fileName += argv[1];
	
	freopen((fileName + ".in").c_str(), "r", stdin);
	freopen((fileName + ".out").c_str(), "w", stdout);
	
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		a[i] = (a[i] >= m);
	}
	
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i)
		qry[i].scan(i);
	
	std::sort(qry + 1, qry + q + 1);
	
	for (int i = 1, cnt = 0, L = 1, R = 1; R <= n; ++R) {
		cnt += a[R];
		while (L <= R && cnt - a[L] >= k) cnt -= a[L++];
		
		if (cnt == k) SegTree::modify(1, 1, n, 1, L, 1);
		
		while (i <= q && qry[i].r == R) {
			ans[qry[i].id] = SegTree::query(1, 1, n, qry[i].l, qry[i].r);
			++i;
		}
	}
	
	for (int i = 1; i <= q; ++i)
		printf("%lld\n", ans[i]);
	
	return 0;
}
