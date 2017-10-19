#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mp make_pair
#define mid ((l+r)>>1)
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int sm = 2e5 + 19;

int cnt;
int n,m;
int w[sm>>1],p[sm];

struct modi {
	int ind,x,w,p;
}q[sm>>1];

vector<int>price[sm];
vector<int>::iterator it;
int lsh[sm];
pii u = mp(0,0);

pii Max(pii x,pii y) {
	if(x.first && y.first) {
		if(x.first != y.first) return x.first > y.first ? x : y;
		return x.second < y.second ? x : y;
	}
	return x.first ? x : y;
}

int Hash(int x) {
	return lower_bound(lsh+1,lsh+cnt+1,x) - lsh;
}
int Binary(int x) {
	int l = 1, r = cnt;
	while(l + 1 < r) {
		//if(lsh[mid] <= x && lsh[mid+1] > x) return mid;
		if(lsh[mid] > x) r = mid-1;
		else l = mid; 
	}
	if(lsh[l] <= x && lsh[l+1] > x)  return l;
	return r;
}

namespace St{
	int Mx[sm<<2],pos[sm<<2];
	
	void Pushup(int rt) {
		if(Mx[rt<<1|1] > Mx[rt<<1]) {
			Mx[rt] = Mx[rt<<1|1];
			pos[rt] = pos[rt<<1|1];
		}
		else {
			Mx[rt] = Mx[rt<<1];
			pos[rt] = pos[rt<<1];
		}
	}
	
	void Build(int rt,int l,int r) {
		if(l == r) {
			if(!price[l].empty()) 
				Mx[rt] = price[l][price[l].size()-1];
			else Mx[rt] = 0;
			pos[rt] = l;
			return ;
		}
		Build(rt<<1,l,mid);
		Build(rt<<1|1,mid+1,r);
		Pushup(rt);
	}
	
	pii Query(int rt,int l,int r,int a,int b) {
		if(a <= l && r <= b) return mp(Mx[rt],pos[rt]);
		pii ans = u;
		if(a <= mid) ans = Max(ans,Query(rt<<1,l,mid,a,b));
		if(b  > mid) ans = Max(ans,Query(rt<<1|1,mid+1,r,a,b));
		return ans; 
	}
	
	void Del(int rt,int l,int r,int p,int k) {
		if(l == r) {
			it = lower_bound(price[l].begin(),price[l].end(),k);
			if(it != price[l].end()) price[l].erase(it);
			if(!price[l].empty()) Mx[rt] = price[l][price[l].size()-1];
			else Mx[rt] = 0;
			return;
		}
		if(p <= mid) Del(rt<<1,l,mid,p,k);
		else Del(rt<<1|1,mid+1,r,p,k);
		Pushup(rt);
	}	
	
	void Ins(int rt,int l,int r,int p,int k) {
		if(l == r) {
			it = upper_bound(price[l].begin(),price[l].end(),k);
			price[l].insert(it,k);
			Mx[rt] = price[l][price[l].size()-1];
			return;
		}
		if(p <= mid) Ins(rt<<1,l,mid,p,k);
		else Ins(rt<<1|1,mid+1,r,p,k);
		Pushup(rt);
	}
	
}

int main() {
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
	
	scanf("%d%d",&n,&m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d",&w[i],&p[i]);
		lsh[++cnt] = p[i];
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d",&q[i].ind);
		if(q[i].ind == 1) {
			scanf("%d%d%d",&q[i].x,&q[i].w,&q[i].p);
			lsh[++cnt] = q[i].p;
		}
		else scanf("%d",&q[i].x),lsh[++cnt] = q[i].x;
	}
	
	sort(lsh+1,lsh+cnt+1);
	cnt = unique(lsh+1,lsh+cnt+1) - lsh - 1;
	
	int pp;
	for(int i = 1; i <= n; ++i) {
		pp = Hash(p[i]);
		if(price[pp].empty())
			price[pp].push_back(w[i]);
		else {
			it = upper_bound(price[pp].begin(),price[pp].end(),w[i]);
			price[pp].insert(it,w[i]);
		}
	}
	
	using namespace St;
	Build(1,1,cnt);
	
	int k,kk,t; LL ans;
	pii vc; 
	for(int i = 1; i <= m; ++i)
		if(q[i].ind == 2) {
			ans = 0;
			k = q[i].x;
			do {
				kk = Binary(k); 
				vc = u;
				vc = Query(1,1,cnt,1,kk);
				if(vc.first) {
					t = k/lsh[vc.second];
					k -= 1ll*t*lsh[vc.second];
					ans += 1ll*vc.first*t;
				}
				else break;
			}while(k);		
			printf("%lld\n",ans);
		}
		else {
			k = q[i].x;
			Del(1,1,n,Hash(p[k]),w[k]);
			Ins(1,1,n,Hash(q[i].p),q[i].w);
			p[k] = q[i].p;
			w[k] = q[i].w;
		}
	
	return 0;		 
}
