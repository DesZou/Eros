#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#define MOD 10000

using namespace std;

typedef long long ll;

int randint() {
  return ((ll)rand()*9971+rand())%1000007;
} 

int main() {
  freopen("3.in","w",stdout);
  srand(time(0));
  int n=100000,m=100000;
  printf("%d %d\n",n,m);
  for(int i=1;i<=n;i++) printf("%d ",randint()%20000+50000);
  printf("\n");
  for(int i=1;i<=n;i++) printf("%d ",1);
  printf("\n");
  for(int i=1;i<=m;i++) {
  	int kind=(rand()%20<4)?1:2;
  	if (kind==1) {
  		int x=randint()%n+1,y=randint()%20000+50000;
  		printf("%d %d %d\n",kind,x,y);
	  }
	else {
		int x=randint()%n+1,y=randint()%n+1;
		if (x>y) swap(x,y);
		printf("%d %d %d\n",kind,x,y);
	}
  }
  return 0;
}
