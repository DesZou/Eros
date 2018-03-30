namespace Eros {
    template<class T, unsigned N>
        struct FenwickTree {
            T elem[N];
            void modify(unsigned, T);
            T sum(unsigned);
        };

    template<class T, unsigned N>
        void FenwickTree<T, N>::modify(unsigned x, const T key)
        {
            for (; x <= N; x += -x & x) elem[x] += key;
        }

    template<class T, unsigned N>
        T FenwickTree<T, N>::sum(unsigned x)
        {
            T res = 0;
            for (; x > 0; x -= -x & x) res += elem[x];
            return res;
        }
}
