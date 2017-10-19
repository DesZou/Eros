#include<bits.stdc++.h>
using namespace std;
#define LL long long
const LL mod=1e9+7;
void read(LL &x)
{
  x=0;
  char c=getchar();
  while(c<'0'||c>'9')
    c=getchar();
  while(c<='9'&&c>='0')
  {
  	x=x*10+c-48;
  	c=getchar();
  }
}
int rd[500050],tot;
queue<int> sp;
int f[500050];
LL va[500050],lens[500050],rech[500550],to[500050],siz[500050],len[500050];
void tpsort(int n)
{
  for(int i=1;i<=n;i++)
    if(!rd[i])
      sp.push(i);
  int p;
  while(!sp.empty())
  {
  	p=sp.front();
  	sp.pop();
  	rd[to[p]]--;
  	if(!rd[to[p]])
  	  sp.push(to[p]);
  }
}
void dfs(int i)
{
  if(rech[i])
    return;
  if(!rech[to[i]])
    dfs(to[i]);
  rech[i]=rech[to[i]];
  va[i]=len[i]*rech[i]+va[to[i]];
  rech[i]++;
  va[i]%=mod;
  return ;
}
int main()
{
  freopen("road.in","r",stdin);
  freopen("road.out","w",stdout);
  LL ans=0,x,y,n;
  read(n);
  for(int i=1;i<=n;i++)
    read(to[i]),read(len[i]),rd[to[i]]++;
  tpsort(n);
  for(int i=1;i<=n;i++)
    if(rd[i]&&(!f[i]))
    {
	  f[i]=++tot;
	  siz[tot]=1;
	  lens[tot]=len[i];
  	  x=to[i];
  	  while(x!=i)
  	    {
  	      f[x]=tot;
  	      lens[tot]+=len[x];
  	      ++siz[tot];
  	      x=to[x];
  	    }
  	  lens[tot]%=mod;
    }
  for(int i=1;i<=n;i++)
    if(f[i]&&(!rech[i]))
    {
      x=i;
      y=siz[f[i]]-1;
      while(to[x]!=i)
      {
      	va[i]+=len[x]*y;
      	--y;
      	va[i]%=mod;
      	x=to[x];
      }
      x=i;
      rech[x]=siz[f[x]];
      while(to[x]!=i)
      {
      	va[to[x]]=va[x]+lens[f[i]]-(siz[f[i]]*len[x]%mod);
      	va[to[x]]%=mod;
		rech[to[x]]=siz[f[x]];
      	x=to[x];
      }
    }
  for(int i=1;i<=n;i++)
    dfs(i);
  for(int i=1;i<=n;i++)
  {
  	ans+=va[i];
  	ans-=n-rech[i];
  }
  if(ans<0)
    ans+=mod;
  cout<<ans%mod;
}
