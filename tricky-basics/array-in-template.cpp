//
// Created by suncx on 2022/12/5.
//

#include <cstddef>
#include <iostream>

using namespace std;

template<typename T, size_t M, size_t N>
bool less(T (&x)[M], T (&y)[N]) {
    for (size_t i = 0; i < M and i < N; ++i) {
        if (x[i] < y[i]) return true;
        if (y[i] < x[i]) return false;
    }
    return M < N;
}

// 只用来处理字符串常量的模板
template<size_t M, size_t N>
bool less(const char (&x)[M], const char (&y)[N]) {
    for (size_t i = 0; i < M and i < N; ++i) {
        if (x[i] < y[i]) return true;
        if (y[i] < x[i]) return false;
    }
    return M < N;
}

int main(int argc, char *argv[]) {

    int x[] = {1, 2, 3};
    int y[] = {1, 2, 3, 4, 5};

    cout << boolalpha << ::less(x, y) << endl;
    cout << boolalpha << ::less("abc", "abcd") << endl;

    return 0;
}
