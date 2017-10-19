#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>

using std::pair;
using std::find;
using std::multiset;

#define Pair pair<LL,LL>

template <typename Tp>Tp Max(const Tp &a, const Tp &b) {return a > b ? a : b;}
template <typename Tp>Tp Min(const Tp &a, const Tp &b) {return a < b ? a : b;}

template <typename Tp>void Read(Tp &x) {
	Tp in = 0, f = 1; char ch = getchar();
	while(ch<'0' || ch>'9') {if(ch=='-') f = -1; ch = getchar();}
	while(ch>='0' && ch<='9') {in = in*10+ch-'0'; ch = getchar();}
	x = in*f;
}

typedef long long LL;

const int SN = 200000 + 10;

const int SM = 100000 + 10;

multiset<LL> num[SN];

Pair max[SN<<2], empty;

LL hashs[SN], n, m;

LL w[SM], p[SM], cnt;

struct POINT {
	int opt;
	LL x, w, p, k;
}Q[SM];

void pushup(int rt) {
	if(max[rt<<1].first >= max[rt<<1|1].first) max[rt] = max[rt<<1];
	else max[rt] = max[rt<<1|1];
}

void Modify(int pos, Pair C, int l, int r, int rt) {
	if(l == r) {
		if(C.first > max[rt].first
		   || (C.first == max[rt].first && C.second < max[rt].second))
			max[rt] = C;
		return ;
	}
	int mid = (l+r)>>1;
	if(pos <= mid) Modify(pos, C, l, mid, rt<<1);
	else Modify(pos, C, mid+1, r, rt<<1|1);
	pushup(rt);
}

void cover(int pos, Pair C, int l, int r, int rt) {
	if(l == r) {
		max[rt] = C; return ;
	}
	int mid = (l+r)>>1;
	if(pos <= mid) cover(pos, C, l, mid, rt<<1);
	else cover(pos, C, mid+1, r, rt<<1|1);
	pushup(rt);
}

void Query(int QL, int QR, int l, int r, int rt, Pair &ans) {
	if(max[rt] == empty) return ;
	if(QL <= l && QR >= r) {
		if(max[rt].first > ans.first ||
		   (max[rt].first == ans.first && max[rt].second < ans.second))
			ans = max[rt];
		return ;
	}
	int mid = (l+r)>>1;
	if(QL <= mid) Query(QL, QR, l, mid, rt<<1, ans);
	if(QR > mid) Query(QL, QR, mid+1, r, rt<<1|1, ans);
}

void Ask(int d) {
	LL ans = 0, now = Q[d].k;

	Pair k;
	
	int pos = 0; 
	
	while(now) {
		if(now < hashs[1]) break;
		if(now >= hashs[cnt]) pos = cnt;
		else {
			pos = std::lower_bound(hashs+1, hashs+cnt+1, now) - hashs;
			if(hashs[pos] > now) pos--;
			if(pos == 0) break;
		}
		k = empty;
		Query(1, pos, 1, cnt, 1, k);
		if(k == empty) break;
		ans += (now/k.second) * k.first;
		now %= k.second;
	}
	printf("%lld\n", ans);
}

void Change(int now) {
	int pos = std::lower_bound(hashs+1, hashs+cnt+1, p[Q[now].x]) - hashs;
	
	cover(pos, empty, 1, cnt, 1);

	num[pos].erase(num[pos].find(w[Q[now].x]));

	if(!num[pos].empty()) {
		Pair f = std::make_pair( (*(--num[pos].end())), hashs[pos]);
		cover(pos, f, 1, cnt, 1);
	}
	
	p[Q[now].x] = Q[now].p, w[Q[now].x] = Q[now].w;

	pos = std::lower_bound(hashs+1, hashs+cnt+1, p[Q[now].x]) - hashs;

	Modify(pos, Pair(Q[now].w, Q[now].p), 1, cnt, 1);

	num[pos].insert(Q[now].w);
}

int main() {
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	
	LL opt = 0, x = 0, pos = 0;
	
	Read(n), Read(m);

	for(int i = 1; i <= n; i++) Read(w[i]), Read(p[i]), hashs[++cnt] = p[i];

	for(int i = 1; i <= m; i++) {
		Read(opt);
		if(opt == 1) {
			Q[i].opt = 1, Read(Q[i].x), Read(Q[i].w), Read(Q[i].p);
			hashs[++cnt] = Q[i].p;
		}
		else Q[i].opt = 2, Read(Q[i].k);
	}

	std::sort(hashs+1, hashs+cnt+1);

	cnt = std::unique(hashs+1, hashs+cnt+1) - hashs - 1;

	for(int i = 1; i <= n; i++) {
		pos = std::lower_bound(hashs+1, hashs+cnt+1, p[i]) - hashs;
		
		Modify(pos, std::make_pair(w[i], p[i]), 1, cnt, 1);

		num[pos].insert(w[i]);
	}

	for(int i = 1; i <= m; i++) {
		if(Q[i].opt == 1) Change(i);
		else Ask(i);
	}

	return 0;
}
