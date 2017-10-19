#include <stdio.h>
#include <iostream>
#include <cstring>
#include <algorithm>
#define lch (x<<1)
#define rch ((x<<1)|1)
typedef long long ll;
const int N=200005;
int n,m,val[N],prc[N],seq[N],v[N],len=0,pos[N];
int mx[N<<2];
using namespace std;

struct option
{
	int typ,x,w,p;
}opt[N];
inline int read()
{
	char c;int x;
	while (c=getchar(),c<'0' || c>'9');x=c^'0';
	while (c=getchar(),c>='0' && c<='9') x=(x<<1)+(x<<3)+(c^'0');
	return x;
}
bool cmp(int a,int b){return v[a]<v[b];}
void update(int x,int l,int r,int p,int v)
{
	if (l==r){mx[x]=v;return;}
	int mid=l+r>>1;
	if (mid>=p) update(lch,l,mid,p,v);
	else update(rch,mid+1,r,p,v);
	mx[x]=max(mx[lch],mx[rch]);
}
void modify(int x,int v,int p)
{
	update(1,1,len,prc[x],0);
	update(1,1,len,p,v),prc[x]=p;
}
int query(int x,int l,int r,int p)
{
	if (l>p) return 0;
	if (l==r) return mx[x];
	int mid=l+r>>1;
	if (mid>p) return query(lch,l,mid,p);
	return max(mx[lch],query(rch,mid+1,r,p));
}
int qprc(int x,int l,int r,int p,int now)
{
	if (l==r) return v[l];
	int mid=l+r>>1;
	if (mid>p || mx[lch]==now) return qprc(lch,l,mid,p,now);
	return qprc(rch,mid+1,r,p,now);
}
int find(int k)
{
	int lb=0,rb=len+1,mid;
	while (lb<rb-1)
	{
		mid=lb+rb>>1;
		if (v[mid]<=k) lb=mid;
		else rb=mid;
	}
	return lb;
}
int main()
{
	freopen ("shopping.in","r",stdin);
	freopen ("shopping.out","w",stdout);
	scanf ("%d %d",&n,&m);
	int i;
	for (i=1;i<=n;i++) val[i]=read(),prc[i]=read(),v[++len]=prc[i];
	for (i=1;i<=m;i++)
	{
		opt[i].typ=read();
		if (opt[i].typ==2) opt[i].x=read();
		else opt[i]=(option){1,read(),read(),read()},v[++len]=opt[i].p;
	}
	for (i=1;i<=len;i++) seq[i]=i;
	sort(seq+1,seq+1+len,cmp);
	sort(v+1,v+1+len);
	for (i=1;i<=len;i++) pos[seq[i]]=i;
	for (i=1;i<=n;i++) update(1,1,len,pos[i],val[i]),prc[i]=pos[i];
	int np=n;
	for (i=1;i<=m;i++)
	if (opt[i].typ==1) np++,modify(opt[i].x,opt[i].w,pos[np]);
	else
	{
		int res=opt[i].x;
		ll ans=0;
		while (res)
		{
			int npos=find(res);
			int rtn=query(1,1,len,npos);
			if (!rtn) break;
			int price=qprc(1,1,len,npos,rtn);
			ans+=(ll)rtn*(res/price),res%=price;
		}
		printf ("%lld\n",ans);
	}
	return 0;
}

