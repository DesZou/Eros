#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define DEBUG(args...) fprintf(stderr, args)

#define FOR(i, l, r) for(int i=(l), i##_end=(r); i<=i##_end; ++i)
#define REP(i, l, r) for(int i=(l), i##_end=(r); i< i##_end; ++i)
#define DFR(i, l, r) for(int i=(l), i##_end=(r); i>=i##_end; --i)
#define DRP(i, l, r) for(int i=(l), i##_end=(r); i> i##_end; --i)

typedef long long LL;

template<class T>T Min(const T &a, const T &b) {return a < b ? a : b;}
template<class T>T Max(const T &a, const T &b) {return a > b ? a : b;}
template<class T>bool Chkmin(T &a, const T &b) {return a > b ? a=b, 1 : 0;}
template<class T>bool Chkmax(T &a, const T &b) {return a < b ? a=b, 1 : 0;}

namespace FI {
	const int SIZE = 1 << 15 | 1;
	char buf[SIZE], *front, *back;
	void NextChar(char &c) {
		if(front == back) back = (front=buf) + fread(buf, 1, SIZE, stdin);
		c = front==back ? (char)EOF : *front++;
	}
	void NextInt(int &x) {
		char c;
		for(NextChar(c); c>'9'||c<'0'; NextChar(c)) ;
		for(x=0; c>='0'&&c<='9'; NextChar(c)) x = (x<<3)+(x<<1)+c-'0';
	}
}

const int SN = 100000 + 47;
const int SM = SN << 1 | 1;
const int ST = 1 << 19 | 1;
const int INF = 0x3f3f3f3f;

struct query {
	int t, x, p, q;
};

std::multiset<int> set[ST];
std::pair<int, int> a[SN], b[SM];
int tree[ST], n, cnt, m, tot, sz, c[SM];
query q[SN];
LL ans;

void Modify(int);
int Ask(int);

int main() {

	freopen("shopping.in", "r", stdin);
	freopen("shopping.out", "w", stdout);

	int t, x, y, z;
	
	FI::NextInt(n), FI::NextInt(m);
	FOR(i, 1, n) {
		FI::NextInt(a[i].second), FI::NextInt(a[i].first);
		b[++tot] = std::make_pair(a[i].first, i);
	}
	FOR(i, 1, m) {
		FI::NextInt(q[i].t);
		if(q[i].t & 1) {
			FI::NextInt(q[i].x), FI::NextInt(q[i].q), FI::NextInt(q[i].p);
			b[++tot] = std::make_pair(q[i].p, n + i);
		}
		else
			FI::NextInt(q[i].x);
	}

	std::sort(b + 1, b + tot + 1), cnt = 0;
	FOR(i, 1, tot) {
		if(b[i].first != b[i - 1].first) c[++cnt] = b[i].first;
		if(b[i].second > n) q[b[i].second - n].p = cnt;
		else a[b[i].second].first = cnt;
	}
	sz = cnt, c[++sz] = INF;
	
	cnt += 2; while(cnt != (cnt & -cnt)) cnt += cnt & -cnt;
	FOR(i, 0, cnt) set[i].insert(0);
	FOR(i, 1, n) set[a[i].first].insert(a[i].second);
	REP(i, 1, cnt) tree[cnt + i] = *set[i].rbegin();
	DFR(i, cnt - 1, 1) tree[i] = Max(tree[i << 1], tree[i << 1 | 1]);

	FOR(i, 1, m) {
		//DEBUG("[%d] : %d %d %d %d\n", i, q[i].t, q[i].x, q[i].p, q[i].q);
		if(q[i].t & 1) {
			std::pair<int, int> &p = a[q[i].x];
			set[p.first].erase(set[p.first].find(p.second)), Modify(p.first);
			p = std::make_pair(q[i].p, q[i].q);
			set[p.first].insert(p.second), Modify(p.first);
		}
		else {
			ans = 0, x = q[i].x;
			while(y = std::upper_bound(c + 1, c + sz + 1, x) - c - 1) {
				z = Ask(y), t = *set[z].rbegin();
				if(!t) break;
				ans += 1LL * x / c[z] * t, x %= c[z];
			}
			printf("%lld\n", ans);
		}
	}
	
	return 0;

}

void Modify(int x) {
	tree[x + cnt] = *set[x].rbegin(), x += cnt;
	while(x >>= 1) tree[x] = Max(tree[x << 1], tree[x << 1 | 1]);
}

int Ask(int p) {
	int max = 0, ret = 1;
	for(int l = cnt, r = cnt + p + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
		if(~l & 1) Chkmax(max, tree[l ^ 1]);
		if( r & 1) Chkmax(max, tree[r ^ 1]);
	}
	while(ret < cnt) ret = tree[ret << 1] >= max ? ret << 1 : ret << 1 | 1;
	return ret - cnt;
}
