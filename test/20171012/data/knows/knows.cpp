#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define rep(i,a,b) for(int i = a; i <= b; i++)
#define dep(i,a,b) for(int i = a; i >= b; i--) 
#define Rep(i,a) for(int i = 0; i < a; i++)
#define pb(a) push_back(a)
#define mp(a,b) make_pair(a,b)
#define ab(x) ((x) < 0 ? -(x) : (x))
using namespace std;
typedef long long LL;
typedef map<int, int>::iterator mit;
typedef set<int>::iterator sit;

const int N = 5e5 + 10, inf = 2e9 + 5;
int n, p[N], w[N];

typedef pair<int, int> sta;

int f[N];

#define mid ((l + r) >> 1)
#define lc (x << 1)
#define rc (lc | 1)
#define lcq lc, l, mid
#define rcq rc, mid + 1, r

sta s[N << 2], sr[N << 2];
sta operator + (const sta &a, const sta &b) { return b.first == inf ? a : mp(b.first, min(a.second, b.second)); }
void build(int x, int l, int r) { s[x] = sr[x] = mp(inf, inf); if (l < r) build(lcq), build(rcq); }

int a, b, c, d; 
sta calc(int x, int l, int r, sta d) {
	if (l == r) return d > s[x] ? s[x] : mp(inf, inf);
	if (s[lc] < d) return calc(lcq, d) + sr[x];
	else return calc(rcq, d);
}
void upd(int x, int l, int r) { sr[x] = calc(rcq, s[lc]), s[x] = s[lc] + sr[x]; }
void modi(int x, int l, int r) {
	if (l == r) s[x] = mp(c, d);
	else (a <= mid ? modi(lcq) : modi(rcq)), upd(x, l, r);
}
void qry(int x, int l, int r, sta &d) {
	if (a <= l && r <= b) d = d + calc(x, l, r, d); else {
		if (a <= mid) qry(lcq, d); if (b > mid) qry(rcq, d);
	}	
}

int main() {
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",p + i);
	rep(i,1,n) scanf("%d",w + i);
	build(1, 1, n);			
	dep(i,n,1) {
		a = p[i], b = n; sta t = mp(inf, inf); qry(1, 1, n, t);
		f[i] = (t.first < inf) ? (w[i] + t.second) : w[i];
		a = p[i], c = i, d = f[i]; modi(1, 1, n);
	}
	a = 1, b = n; sta t = mp(inf, inf); qry(1, 1, n, t);
	cout <<t.second<<endl;
	return 0;
}