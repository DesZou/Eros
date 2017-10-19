#include<cstdio>
#include<cstring>

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

template <typename tp>
inline tp max (const tp& x, const tp& y) { return (x > y)? x: y ; }
template <typename tp>
inline tp min (const tp& x, const tp& y) { return (x < y)? x: y ; }
template <typename tp>
inline bool chkmax (tp& x, const tp& y) {
	return (x >= y)? (false): (x = y, true) ;
}
template <typename tp>
inline bool chkmin (tp& x, const tp& y) {
	return (x <= y)? (false): (x = y, true) ;
}

template <typename tp>
inline tp scanf (tp& in) {
	in = 0 ; char ch = getchar() ; tp f = 1 ;
	for (; ch> '9' || ch< '0' ; ch = getchar()) if (ch == '-') f = -1 ;
	for (; ch>='0' && ch<='9' ; ch = getchar()) in = in * 10 + ch - '0' ;
	return in *= f ;
}

static const int maxn = 5e5 + 11 ;
static const int mod = 1e9 + 7 ;

int n ;
int tp ;
int dct ;
int cnt ;

int to[maxn] ;
int li[maxn] ;
int ans[maxn] ;
int reach[maxn] ;
bool vis[maxn] ;

int dfn[maxn] ;
int low[maxn] ;
int bel[maxn] ;
int vev[maxn] ;
int size[maxn] ;
int stack[maxn] ;
bool V[maxn] ;

inline int add (int x, int y) {
	x += y ; if (x >= mod) x -= mod ; return x ;
}

inline int minus (int x, int y) {
	x -= y ; if (x < 0) x += mod ; return x ;
}

inline int mul (int x, int y) {
	return 1LL * x * y % mod ;
}

void tarjan (int x) {
	V[x] = true ; stack[++tp] = x ;
	dfn[x] = low[x] = ++dct ;
	if (!dfn[to[x]]) tarjan (to[x]), chkmin (low[x], low[to[x]]) ;
	else if (V[to[x]]) chkmin (low[x], dfn[to[x]]) ;
	if (dfn[x] != low[x]) return ;
	int y ; ++cnt ;
	do {
		y = stack[tp--] ;
		V[y] = false ;
		bel[y] = cnt ;
		size[cnt]++ ;
		vev[cnt] = add (vev[cnt], li[y]) ;
	} while (x != y) ;
}

inline void work (int x) {
	int tot = 1, sum = li[x] ; vis[x] = true ;
	for (int i = to[x] ; i ^ x ; i = to[i])
		++tot, sum = add (sum, li[i]), vis[i] = true ;
	int fir = mul (tot - 1, li[x]), t = tot - 1 ;
	for (int i = to[x] ; i ^ x ; i = to[i])
		fir = add (fir, mul (li[i], --t)), reach[i] = tot ;
	ans[x] = fir ; reach[x] = tot ;
	for (int i = to[x], lst = x ; i ^ x ; lst = i, i = to[i])
		ans[i] = minus (add (ans[lst], sum), mul (tot, li[lst])) ;
}

void dfs (int x) {
	vis[x] = true ;
	if (!vis[to[x]]) dfs (to[x]) ;
	reach[x] = reach[to[x]] + 1 ;
	ans[x] = add (ans[to[x]], mul (reach[x] - 1, li[x])) ;
}

int main() {
	
	freopen ("t.in", "r", stdin) ;
	freopen ("t.out", "w", stdout) ;
	
	scanf(n) ;
	FOR (i, 1, n) scanf(to[i]), scanf(li[i]) ;
	
	FOR (i, 1, n) if (!dfn[i]) tarjan (i) ;
	
	memset (V, 0, sizeof V) ;
	FOR (i, 1, n) if (!V[bel[i]] && size[bel[i]] > 1)
		V[bel[i]] = true, work (i) ;
	
	FOR (i, 1, n) if (to[i] == i) vis[i] = true, reach[i] = 1 ;
	FOR (i, 1, n) if (!vis[i]) dfs (i) ;
	
	int answer = 0 ;
	FOR (i, 1, n)
		answer = add (answer, minus (ans[i], n - reach[i])) ;
	
	printf ("%d\n", answer) ;
	
	return 0 ;
}
