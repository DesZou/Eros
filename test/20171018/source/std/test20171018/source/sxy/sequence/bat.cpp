//Serene
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<cmath>
using namespace std;
int tot;

int main() {
	while(++tot) {
		printf("Case %d:\n",tot);
		system("rand > rand.txt");
		system("force < rand.txt > std.out");
		if(system("sequence < rand.txt > test.out")) printf("ERROR!\n");
		if(system("fc std.out test.out")) {
			printf("WRONG ANSWER!\n");
			system("rand.txt");
			system("pause");
		}
		else printf("PASSED...\n\n\n");
	}
	return 0;
}

