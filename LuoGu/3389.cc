#include <cstdio>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

const size_t Size = 100 + 5;
const double Inf = 1.00 / 0;

struct Matrix {
    double e[Size * Size];
    int line, col;

    Matrix(int x, int y): line(x), col(y) {
        std::memset(e, 0, sizeof e);
    }

    inline double& operator()(const int &i, const int &j) {
        return *(e + (i - 1) * col + j - 1);
    }
};

Matrix operator*(Matrix &a, Matrix &b) {
    if(a.col != b.line) std::exit(-1);
    Matrix res(a.line, b.col);
    for(int i = 1; i <= a.line; ++i)
        for(int k = 1; k <= a.col; ++k)
            for(int j = 1; j <= b.col; ++j)
                res(i, j) += a(i, k) * b(k, j);
    return res;
}

std::ostream& operator<<(std::ostream &out, Matrix &a) {
    out << "┌";
    for(int i = 1; i <= a.col; ++i)
        for(int j = 1; j <= 10; ++j) out << "─";
    out << "┐\n";
    for(int i = 1; i <= a.line; ++i) {
        out << "│";
        for(int j = 1; j <= a.col; ++j) out << std::setw(10) << a(i, j);
        out << "│\n";
    }
    out << "└";
    for(int i = 1; i <= a.col; ++i)
        for(int j = 1; j <= 10; ++j) out << "─";
    out << "┘\n";
    return out;
}

std::istream& operator>>(std::istream &in, Matrix &a) {
    for(int i = 1; i <= a.line; ++i)
        for(int j = 1; j <= a.col; ++j)
            in >> a(i, j);
    return in;
}

void gaussElimination(Matrix &a) {
    for(int i = 1, r; i <= a.line; ++i) {
        r = i;

        for(int j = i + 1; j <= a.line; ++j)
            if(std::abs(a(j, i)) > std::abs(a(r, i))) r = j;

        if(r != i) for(int j = 1; j <= a.col; ++j)
            std::swap(a(r, j), a(i, j));

        for(int j = i + 1; j <= a.line; ++j) {
            double f = a(j, i) / a(i, i);
            for(int k = i; k <= a.col; ++k)
                a(j, k) -= f * a(i, k);
        }
    }

    if(a(a.line, a.col) == 0) {
        a(a.line, a.col) = Inf;
        return;
    }

    for(int i = a.line; i > 0; --i) {
        for(int j = i + 1; j < a.col; ++j)
            a(i, a.col) -= a(j, a.col) * a(i, j);
        a(i, a.col) /= a(i, i);
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    int n;

    std::cin >> n;
    
    static Matrix d(n, n + 1);

    std::cin >> d;

    gaussElimination(d);

    if(d(n, n + 1) == Inf) {
        std::cout << "No Solution" << std::endl;
        return 0;
    }

    std::cout.precision(2);
    std::cout.setf(std::ios_base::fixed, std::ios_base::floatfield);

    for(int i = 1; i <= n; ++i)
        std::cout << d(i, n + 1) << '\n';

    return 0;
}
