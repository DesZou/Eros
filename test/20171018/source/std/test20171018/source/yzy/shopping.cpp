#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>

#define Rep(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i<=(i##_END);++i)
#define For(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i!=(i##_END);++i)
#define Lop(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i>=(i##_END);--i)
#define Dnt(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i!=(i##_END);--i)

#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#define Newline (putchar(10))

using std :: max;
using std :: min;

typedef long long LL;
typedef std :: pair<int, int> ii;

template <class T> bool chkmax(T &x, const T &y){
	return y > x? x = y, true : false;
} 
template <class T> bool chkmin(T &x, const T &y){
	return y < x? x = y, true : false;
}

namespace FI{

	const int L = 1 << 15 | 1;
	char buffer[L], *S, *T;

	inline char Getchar(){
		if(S == T) T = (S = buffer) + fread(buffer, 1, L, stdin);
		return S == T? EOF : *S ++;
	}

	template <class T> void read(T &in){
		char ch; int f = 1;
		for(ch = Getchar(); !isdigit(ch); ch = Getchar()) if(ch == '-') f = -1;
		for(in = 0; isdigit(ch); ch = Getchar()) in = in * 10 + ch - '0';
		in *= f;
	}
	
}

const int maxx = 100000 + 25;
const int Inf = 1e9 + 25;

int n, m, x, y, z, k, num;
int cnt, tot;

int w[maxx], p[maxx];
int tmp[maxx << 1];
ii  Tx[maxx << 3];

LL  ans;

class Node{
public:
	int f;
	int w, p, k;
};

Node A[maxx];

std :: multiset<int> S[maxx << 1];
std :: multiset<int> :: iterator it;

namespace Segment_Tree{

	void modify(int i, int pos, int l, int r, int k, int f){
		if(l == r){
			if(f == 1){
				S[l].insert(k);
			}
			else{
				it = S[l].lower_bound(k);
				S[l].erase(it);
			}
			if(S[l].empty()) Tx[i] = ii(0, -l);
			else{
				it = S[l].end();
				-- it;
				Tx[i] = ii(*it, -l);
			}
			return;
		}
		int mid = (l + r) >> 1;
		if(pos <= mid) modify(i << 1, pos, l, mid, k, f);
		else modify(i << 1 | 1, pos, mid + 1, r, k, f);
		if(Tx[i << 1] >= Tx[i << 1 | 1]) Tx[i] = Tx[i << 1];
		else Tx[i] = Tx[i << 1 | 1];
	}

	ii  Query(int i, int x, int y, int l, int r){
		if(x <= l && r <= y) return Tx[i];
		ii ans = ii(0, -Inf);
		int mid = (l + r) >> 1;
		if(x <= mid)		
			ans = max(ans, Query(i << 1, x, y, l, mid));
		if(y >  mid)
			ans = max(ans, Query(i << 1 | 1, x, y, mid + 1, r));
		return ans;
	}
	
}

using namespace FI;
using namespace Segment_Tree;

int main(){

	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);
	
    read(n); read(m);

	Rep(i, 1, n){
		read(w[i]); read(p[i]);
		tmp[i] = p[i];
	}

	cnt = n;

	Rep(i, 1, m){
		read(A[i].f);
		if(A[i].f == 1){
			read(A[i].k); read(A[i].w); read(A[i].p);
			tmp[ ++ cnt] = A[i].p;
 		}
		else{
			read(A[i].k);
		}
	}

	std :: sort(tmp + 1, tmp + cnt + 1);
	tot = std :: unique(tmp + 1, tmp + cnt + 1) - tmp - 1;

	Rep(i, 1, n)
		p[i] = std :: lower_bound(tmp + 1, tmp + tot + 1, p[i]) - tmp;
	Rep(i, 1, m)
		if(A[i].f == 1)
			A[i].p = std :: lower_bound(tmp + 1, tmp + tot + 1, A[i].p) - tmp;

	Rep(i, 1, n)
		modify(1, p[i], 1, tot, w[i], 1);

	Rep(i, 1, m){

		if(A[i].f == 1){
			int pos = A[i].k;
			modify(1, p[pos], 1, tot, w[pos], -1);
			w[pos] = A[i].w; p[pos] = A[i].p;
			modify(1, p[pos], 1, tot, w[pos], 1);
		}

		if(A[i].f == 2){
			k = A[i].k;
			ans = 0;
			while(true){
				int pos = 0;
				if(k < tmp[1]) break;
				else if(k >= tmp[tot])
					pos = tot;
				else
					pos = std :: upper_bound(tmp + 1, tmp + tot + 1, k) - tmp - 1;
				ii u = Query(1, 1, pos, 1, tot);
				u.second = -u.second;
				int cur = k / tmp[u.second], res = k % tmp[u.second];
				ans += 1ll * u.first * 1ll * cur;
				k = res;
			}
			printf("%lld\n", ans);
		}
		
	}

	return 0;
}
