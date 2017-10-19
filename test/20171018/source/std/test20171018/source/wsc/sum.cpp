#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <algorithm>
#define THE_BEST_PONY "Rainbow Dash"

using namespace std;
typedef long long LL;

LL QMul(LL a,LL b,LL p){
	LL re=0;
	a%=p; b%=p;
	while(b){
		if(b&1) re=(re+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	return re;
}

int n;
LL p,ans,s;

int main(){
	freopen("sum.in","r",stdin);
	freopen("sum.out","w",stdout);
	scanf("%d%lld",&n,&p);
	for(int i=0;i<n;i++){
		LL a;
		scanf("%lld",&a);
		s=QMul(s+1,a,p);
		ans=(ans+s)%p;
	}
	printf("%lld",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}

