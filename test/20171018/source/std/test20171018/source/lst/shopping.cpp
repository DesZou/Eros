#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

template <typename ty> void read(ty &x) {
	x = 0; int f = 1; char ch = getchar();
	while (ch > '9' || ch < '0') { if (ch == '-') f = -1; ch = getchar(); }
	while (ch >= '0' && ch <= '9') { x = x*10 + ch - '0'; ch = getchar(); }
	x *= f;
}
template <typename ty> ty Max(ty a, ty b) { return a > b ? a : b; }
template <typename ty> ty Min(ty a, ty b) { return a < b ? a : b; }

typedef long long LL;
typedef double db;
const int N = 1e5 + 5;

struct thing {
	int w, p;
}W[N];

int P[N], PRE[N];
int n, m;

bool cmp(thing a, thing b) {
	return a.w == b.w ? a.p > b.p : a.w < b.w;
}

int query(int x) {
	LL ans = 0;
	while (x <= n) {
		ans += P[x];
		x += (x  & (-x));
	}
	return ans;
}

void add(int x, int v) {
	while (x) {
		P[x] += v;
		x -= (x & (-x));
	}
}

int find(int x) { return PRE[x] == x ? x : PRE[x] = find(PRE[x]); }

int main() {
	
	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	
	read(n); read(m);
	for (int i = 1; i <= n; ++ i) {
		read(W[i].w); read(W[i].p);
	}
	sort(W + 1, W + n + 1, cmp);
	
	for (int i = n, f; i >= 1; -- i) {
		if (W[i].w != W[i + 1].w) f = i;
		PRE[i] = f;
	}
	
	int opt, x, w, p;
	int l, r, td, a, b, c, d;
	thing ft, lt;
	for (int i = 1; i <= m; ++ i) {
		read(opt); read(x);
		if (opt == 1) {
			read(w); read(p);
			td = x + query(x);
			if (W[td].w < w) d = 1;
			else if (W[td].w > w) d = -1;
			else if (W[td].p < p) d = -1;
			else if (W[td].p > p) d = 1;
			else continue;
			ft = W[1 + query(1)];
			lt = W[n + query(n)];
			if (w < ft.w || (w == ft.w && p >= ft.p) ) {
					add(x, -1);
					int f = query(1) + 1;
					add(1, td - f + 1);
			}
			else if (w > lt.w || (w == lt.w && p <= lt.p) ) {
					add(n - 1, 1); add(x - 1, -1);
					int f = query(n) + n;
					add(n, td - f); add(n - 1, f - td);
			}
			else {
				if (d == 1) l = x + 1, r = n - 1;
				else l = 1, r = x - 2; a = l;
				while (l <= r) {
					int mid = l + r >> 1;
					b = find(mid + query(mid));
					c = find(mid + 1 + query(mid + 1));
					if (W[b].w <= w && w <= W[c].w && W[b].p >= p && p >= W[c].p) {
						a = mid; break;
					}
					else if (W[b].w > w) r = mid - 1;
					else if (w > W[c].w) l = mid + 1;
					else if (W[b].p < p) r = mid - 1;
					else l = mid + 1;
				}
				if (d == 1) {
					add(a - 1, 1); add(x - 1, -1);
					int f = query(a) + a;
					add(a, td - f); add(a - 1, f - td);
				}
				else {
					add(x, -1); add(a + 2, 1);
					int f = query(a + 1) + a + 1;
					add(a + 1, td - f); add(a, f - td);
				}
			}
			W[x].p = p; W[x].w = w;
		}
		else {
			LL to = 0;
			while (x) {
				l = 1; r = n; a = 0;
				while (l <= r) {
					int mid = l + r >> 1;
					b = find(mid + query(mid));
					if (W[b].p <= x) { a = b; l = mid + 1; }
					else r = mid - 1;
				}
				if (a == 0) break;
				to += 1ll * W[a].w * (x / W[a].p);
				x %= W[a].p;
			}
			printf("%lld\n", to);
		}
	}
	
	return 0;
	
}
