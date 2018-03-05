#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

const size_t Size = 1e6 + 5;

int h[Size];

int main() {
    int n;
    std::scanf("%d", &n);

    int *head = h, *tail = h;

    for(int cmd; n --> 0;) {
        std::scanf("%1d", &cmd);
        if(cmd == 1) {
            std::scanf("%d", tail);
            std::push_heap(head, ++tail, std::greater<int>());
        } else if(cmd == 2) {
            std::printf("%d\n", *head);
        } else {
            std::pop_heap(head, tail--, std::greater<int>());
        }
    }

    return 0;
}
