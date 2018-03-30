#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;

const char El = 10;
const int Size = 5e4 + 5;

template<class T, int N>
struct FenwickTree {
    T elem[N];
    void modify(int, T);
    T sum(int);
};

long long val[Size];
long long sum[Size];

FenwickTree<long long, Size> ans;

int n;

template<class T, int N> void FenwickTree<T, N>::modify(int x, const T key)
{
    for (; x <= N; x += -x & x) elem[x] += key;
}

template<class T, int N> T FenwickTree<T, N>::sum(int x)
{
    T res = 0;
    for (; x > 0; x -= -x & x) res += elem[x];
    return res;
}

int main()
{
    cin.sync_with_stdio(0);

    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> val[i];
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + val[i];
    for (int i = 1; i <= n; ++i) ans.modify(i, val[i] - val[i - 1]);

    for (int i = 1, opt, l, r, c; i <= n; ++i) {
        cin >> opt >> l >> r >> c;
        if (opt == 0) {
            ans.modify(l, c);
            ans.modify(r + 1, -c);
        } else {
            cout << ans.sum(r) << El;
        }
    }

    return 0;
}
