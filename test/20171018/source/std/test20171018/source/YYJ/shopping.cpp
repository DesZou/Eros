//El Psy Congroo
#include <cstdio>
#include <cmath>
#include <queue>
#include <algorithm>
#include <cstring>
#include <climits>
#define LL long long
#define MAXN 200000
using namespace std;
int n,m,num,now;
int w[MAXN],p[MAXN],b[MAXN],sw[MAXN];
int mx[MAXN<<2],mxp[MAXN<<2],rnk[MAXN],list[MAXN];
int rrnk[MAXN];
LL ans;

struct Date{
	int opt,x,y,z;
}op[MAXN];

bool cmp(const int a,const int b) {return p[a]<p[b];}

void pushup(int rt)
{
	if(mx[rt<<1]>mx[rt<<1|1]) 
		mx[rt]=mx[rt<<1],mxp[rt]=mxp[rt<<1];
	else if(mx[rt<<1]<mx[rt<<1|1]) 
		mx[rt]=mx[rt<<1|1],mxp[rt]=mxp[rt<<1|1];
	else if(mx[rt<<1]==mx[rt<<1|1]) 
		mx[rt]=mx[rt<<1],mxp[rt]=min(mxp[rt<<1],mxp[rt<<1|1]);
}

void update(int p,int x,int l,int r,int rt)
{
	if(l==r) return mx[rt]=x,mxp[rt]=p,void();
	int mid=(l+r)>>1;
	if(p<=mid) update(p,x,l,mid,rt<<1);
	if(mid<p) update(p,x,mid+1,r,rt<<1|1);
	pushup(rt);
}

int query(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R) return mxp[rt];
	int mid=(l+r)>>1,ls=0,rs=0;
	if(L<=mid) ls=query(L,R,l,mid,rt<<1);
	if(mid<R) rs=query(L,R,mid+1,r,rt<<1|1);
	if(sw[ls]>=sw[rs]) return ls;
	else return rs;
}


LL ask(int k)
{
	ans=0;int r=0;
	LL ww=0,ti=0;
	while(k)
	{
		r=upper_bound(b+1,b+num+1,k)-b-1;
		if(!r) break;
		ww=query(1,r,1,num,1);
		if(!sw[ww]) break;
		ans+=(LL)(k/b[ww])*sw[ww];
		k%=b[ww];
	}
	printf("%lld\n",ans);
}

void mody(int x,int ww,int pp)
{
	++now;
	update(rrnk[x],0,1,num,1);
	sw[rrnk[x]]=0;
	rrnk[x]=rnk[now];
	update(rrnk[x],ww,1,num,1);
	sw[rrnk[x]]=ww;
}

int main()
{
	freopen("shopping.in","r",stdin);
	freopen("shopping.out","w",stdout);
  scanf("%d%d",&n,&m);
  for(int i=1;i<=n;i++)
  	scanf("%d%d",&w[i],&p[i]),b[++num]=p[i],list[num]=num;
  for(int i=1;i<=m;i++)
  {
  	scanf("%d%d",&op[i].opt,&op[i].x);
  	if(op[i].opt==1) 
  		scanf("%d%d",&op[i].y,&op[i].z),
  		b[++num]=op[i].z,w[num]=op[i].y,p[num]=op[i].z,list[num]=num;
  }

 	sort(list+1,list+num+1,cmp);
 	
 	for(int i=1;i<=num;i++) rnk[list[i]]=i;
 	for(int i=1;i<=n;i++) rrnk[i]=rnk[i];
  sort(b+1,b+num+1);
  now=n;
  for(int i=1;i<=n;i++) 	 
  {
  	update(rnk[i],w[i],1,num,1);
  	sw[rnk[i]]=w[i];
  }
  
	for(int i=1;i<=m;i++)
  {
  	if(op[i].opt==2) ask(op[i].x);
  	else mody(op[i].x,op[i].y,op[i].z);
  }
  
	return 0;
}
/*

3 3
5 3
5 2
5 5
1 3 5 1
1 3 5 1
2 1

*/
