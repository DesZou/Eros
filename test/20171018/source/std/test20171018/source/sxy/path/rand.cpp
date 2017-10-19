//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<ctime>
using namespace std;
const int n=500,m=124750;

int main() {
	srand((unsigned)time(NULL));
	freopen("path.in","w",stdout);
	cout<<n<<" "<<m<<"\n";
	for(int i=1;i<=n;++i) cout<<rand()<<" ";
	cout<<"\n";
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) {
		cout<<i<<" "<<j<<" "<<rand()<<"\n";
	}
	return 0;
}

