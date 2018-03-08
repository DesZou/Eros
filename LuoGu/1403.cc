#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

using std::cin;
using std::cout;
using std::cerr;

const char El = 10;

int n;

int main() {
    long long ans = 0;

    cin >> n;

    for (int i = 1; i <= n; ++i) ans += (long long)n / i;

    cout << ans << El;

    return 0;
}