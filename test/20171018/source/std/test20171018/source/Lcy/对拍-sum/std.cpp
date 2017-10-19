#include<bits/stdc++.h>
using namespace std ;

#define For(i, _begin, _end) \
for (int i = (_begin), i##end = (_end) ; i <= (i##end) ; ++i)
#define Lop(i, _begin, _end) \
for (int i = (_begin), i##end = (_end) ; i >= (i##end) ; --i)
#define Rep(i, _begin, _add) \
for (int i = (_begin) ; i ; i = (_add))
#define FOR(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end) ; i <= (i##end) ; ++i)
#define LOP(i, _begin, _end) \
for (register int i = (_begin), i##end = (_end) ; i >= (i##end) ; --i)
#define REP(i, _begin, _add) \
for (register int i = (_begin) ; i ; i = (_add))

typedef long long LL ;

static const int maxn = 1e6 + 11 ;

namespace sum {
	int n ;
	LL mod ;
	
	int ai[maxn] ;
	inline void main() {
		scanf( "%d%lld", &n, &mod) ;
		FOR (i, 1, n) scanf ("%d", &ai[i]) ;
		LL ans = 0 ;
		FOR (l, 1, n) {
			LL mul = 1 ;
			FOR (r, l, n) {
				mul = mul * ai[r] % mod ;
				ans = (ans + mul) % mod ;
			}
		}
		printf ("%lld\n", ans) ;
	}
}

namespace road {
	static const int maxm = 2e3 + 11 ;
	static const int mod = 1e9 + 7 ;
	int n ;
	
	int to[maxn] ;
	int len[maxn] ;
	LL dis[maxm][maxm] ;
	bool V[maxm] ;
	inline void main() {
		scanf( "%d", &n) ;
		FOR (i, 1, n) scanf( "%d%d", &to[i], &len[i]) ;
		memset (dis, -1, sizeof dis) ;
		FOR (i, 1, n) {
			LL tot = 0LL ;
			memset (V, 0, sizeof V) ;
			V[i] = true ;
			for (int it = to[i] ; !V[it] ; it = to[it]) {
				V[it] = true ;
				tot += len[it] ;
				tot %= mod ;
				dis[i][it] = tot ;
			}
		}
		LL ans = 0LL ;
		FOR (i, 1, n) FOR (j, 1, n) if (i != j)
			ans = (ans + dis[i][j] + mod) % mod ;
		printf ("%lld\n", ans) ;
	}
}

int main() {
	
	freopen ("t.in", "r", stdin) ;
	freopen ("std.out", "w", stdout) ;
	
	sum :: main() ;
	
	return 0 ;
}
