#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define MOD 1000000000

using namespace std;

typedef long long ll;

int randint() {
  return ((ll)rand()*9573121+rand())%MOD+1;
}

int main() {
  freopen("3.in","w",stdout);
  srand(time(0));
  int n=100000,m=100010;
  printf("%d %d\n",n,m);
  for(int i=1;i<=m-n+1;i++) {
  	int x,y;
  	do {
  		x=rand()%n+1;y=rand()%n+1;
	  } while (x==y);
	printf("%d %d %d\n",x,y,randint());
  }
  for(int i=2;i<=n;i++) printf("%d %d %d\n",rand()%(i-1)+1,i,randint());
  return 0;
}
