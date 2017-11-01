#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstdlib>
#define lowbit(x) (x&-x)

using namespace std;

typedef long long ll;

namespace Treap {

int s[8000000],num[8000000];
int ch[8000000][2],a[8000000],ra[8000000],tot;

inline void update(int o) {
  s[o]=num[o]+s[ch[o][0]]+s[ch[o][1]];
}

int rotate(int x,int y) {
  int d=(ch[y][1]==x);
  ch[y][d]=ch[x][d^1];ch[x][d^1]=y;
  update(y);update(x);
  return x;
}

int insert(int o,int p,int q) {
  if (!o) {
  	o=++tot;
  	s[o]=num[o]=q;
  	a[o]=p;ra[o]=rand();
  	return o;
  }
  if (a[o]==p) {
  	num[o]+=q;s[o]+=q;
  	return o;
  }
  s[o]+=q;
  int d=(p>a[o]);
  ch[o][d]=insert(ch[o][d],p,q);
  if (ra[ch[o][d]]<ra[o]) o=rotate(ch[o][d],o);
  return o;
}

int sum(int o,int p) {
  if (!o) return 0;
  ll v=s[ch[o][0]]+num[o];
  if (a[o]==p) return v;
  if (a[o]>p) return sum(ch[o][0],p);
  return v+sum(ch[o][1],p);
}

}

namespace Fw_Tree {

int root[100005];

void add(int x,int l,int r,int num) {
  for(;x;x-=lowbit(x)) {
  	root[x]=Treap::insert(root[x],l,num);
  	root[x]=Treap::insert(root[x],r+1,-num);
  }
}

int sum(int x,int y,int n) {
  int s=0;
  for(;y<=n;y+=lowbit(y)) 
    s+=Treap::sum(root[y],x);
  return s;
}

}

int c[100005],w[100005];
set <int> st[100005];

int main() {
  freopen("3.in","r",stdin);
  freopen("3.out","w",stdout);
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++) scanf("%d",&c[i]);
  for(int i=1;i<=n;i++) scanf("%d",&w[i]);
  for(int i=1;i<=n;i++) {
  	int x=c[i];
  	st[x].insert(i);
  	set<int>::iterator it=st[x].find(i);
  	int l;
  	if (it==st[x].begin()) l=1; else l=(*(--it))+1;
  	Fw_Tree::add(n,l,i,w[x]);
  	Fw_Tree::add(i-1,l,i,-w[x]);
  }
  for(int i=1;i<=m;i++) {
  	int kind,x,y;
  	scanf("%d%d%d",&kind,&x,&y);
  	if (kind==1) {
  		int v=c[x];
  	    set<int>::iterator it=st[v].find(x),it2=it,it3=it;
  	    int l,r;
  	    if (it2==st[v].begin()) l=1; else l=(*(--it2))+1;
  	    it3++;
  	    if (it3==st[v].end()) r=n; else r=(*it3)-1;
  	    Fw_Tree::add(r,l,x,-w[v]);
  	    Fw_Tree::add(x-1,l,x,w[v]);
  	    st[v].erase(x);
  	    v=y;
  	    st[v].insert(x);
  	    it=st[v].find(x);it2=it;it3=it;
  	    if (it2==st[v].begin()) l=1; else l=(*(--it2))+1;
  	    it3++;
  	    if (it3==st[v].end()) r=n; else r=(*it3)-1;
  	    Fw_Tree::add(r,l,x,w[v]);
  	    Fw_Tree::add(x-1,l,x,-w[v]);
  	    c[x]=y;
	  }
	else printf("%d\n",Fw_Tree::sum(x,y,n));
  }
  return 0;
}
