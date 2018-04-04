/*
 * libreoj 6279
 *
 * 跟分块第二题做法一样，本来可以用平衡树维护的，太慢了。。。
 * 能不用数据结构的就别用了。
 * */
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <array>

using std::cin;
using std::cout;
using std::cerr;
using std::sort;
using std::make_pair;
using std::distance;

const char El = 10;
const int Block = 316 + 5;

std::vector<std::pair<long long, int>> bl[Block];
std::array<int, Block> tag;
std::array<int, Block * Block> bid;
int n, block;

void insert(int, long long);
int query(int, int, long long);
void modify(int, int, long long);
int binSearch(int, int, int, int, int, long long);
void change(int, int, int, int, int, long long);

int main()
{
    cin.sync_with_stdio(0);

    cin >> n;

    block = sqrt(n);

    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        insert(i, x);
    }

    for (int i = 0; i <= block; ++i) sort(bl[i].begin(), bl[i].end());

    for (int i = 1, opt, l, r; i <= n; ++i) {
        long long c;
        cin >> opt >> l >> r >> c;
        if (opt == 0) modify(l - 1, r - 1, c);
        else cout << query(l - 1, r - 1, c) << El;
    }

    return 0;
}

void insert(int pos, long long key)
{
    bid[pos] = pos / block;
    bl[bid[pos]].push_back(make_pair(key, pos));
}

int query(int l, int r, long long key)
{
    int res = -1;
    for (int i = bid[l]; i <= bid[r]; ++i)
        res = std::max(res, binSearch(i, i * block, (i + 1) * block - 1, l, r, key));
    return res;
}

void modify(int l, int r, long long key)
{
    for (int i = bid[l]; i <= bid[r]; ++i)
        change(i, i * block, (i + 1) * block - 1, l, r, key);
}

void change(int x, int l, int r, int s, int t, long long key)
{
    if (l >= s && r <= t) {
        tag[x] += key;
    } else if (t >= l || s <= r) {
        for (auto &i : bl[x])
            if (i.second >= s && i.second <= t) i.first += key;
        sort(bl[x].begin(), bl[x].end());
    }
}

int binSearch(int x, int l, int r, int s, int t, long long key)
{
    if (l >= s && r <= t) {
        auto res = std::lower_bound(bl[x].begin(), bl[x].end(),
                make_pair(key - tag[x], 0));
        return res == bl[x].begin()? -1 : std::prev(res)->first + tag[x];
    } else if (t >= l || s <= r) {
        long long res = -1;
        for (auto &i : bl[x])
            if (i.second >= s &&
                i.second <= t &&
                i.first + tag[x] < key) res = std::max(i.first + tag[x], res);
        return res;
    } else return -1;
}

