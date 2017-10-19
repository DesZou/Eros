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

template <class tp1, class tp2>
inline tp1 Rand (tp2 x) { return rand() % x + 1 ; }

typedef long long LL ;

namespace sum {
	inline void main() {
		int n ;
		n = 1e4 ;
		printf ("%d %lld\n", n, Rand<LL, LL> (1e18)) ;
		FOR (i, 1, n) printf ("%d ", Rand<int, int> (1e9)) ;
		putchar (10) ;
	}
}

namespace road {
	inline void main() {
		int n ;
		n = 1e3 ;
		printf ("%d\n", n) ;
		FOR (i, 1, n)
			printf ("%d %d\n", Rand<int, int> (n), Rand<int, int> (1e9)) ;
	}
}

namespace shopping {
	inline void main() {
		int n, m ;
		n = 1e5 ; m = 1e5 ;
		printf ("%d %d\n", n, m) ;
		FOR (i, 1, n)
			printf ("%d %d\n", Rand<int, int> (1e9), Rand<int, int> (1e4)) ;
		FOR (i, 1, m) {
			int op = Rand<int, int> (2) ;
			if (op == 1) {
				int x = Rand<int, int> (n), w = Rand<int, int> (1e9),
					p = Rand<int, int> (1e4) ;
				printf ("%d %d %d %d\n", op, x, w, p) ;
			} else printf ("%d %d\n", op, Rand<int, int> (1e9)) ;
		}
	}
}

int main() {
	
	srand (time(NULL)) ;
	
	freopen ("t.in", "w", stdout) ;
	
	shopping :: main() ;
	
	return 0 ;
}
