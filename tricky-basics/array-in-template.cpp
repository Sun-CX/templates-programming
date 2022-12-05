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

// 某些情况下可能也必须去为边界未知的数组做重载或者部分特化。下面的代码展示了对数组所做的所有可能的重载
template<typename T>
struct MyClass;

// 对于已知边界的数组的偏特化
template<typename T, size_t SZ>
struct MyClass<T[SZ]> {
    static void print() {
        cout << "print() for T[" << SZ << ']' << endl;
    }
};

// 对于已知边界的数组引用的偏特化
template<typename T, size_t SZ>
struct MyClass<T(&)[SZ]> {
    static void print() {
        cout << "print() for T(&)[" << SZ << ']' << endl;
    }
};

// 对于未知边界的数组的偏特化
template<typename T>
struct MyClass<T[]> {
    static void print() {
        cout << "print() for T[]" << endl;
    }
};

// 对于未知边界的数组引用的偏特化
template<typename T>
struct MyClass<T(&)[]> {
    static void print() {
        cout << "print() for T(&)[]" << endl;
    }
};

// 对指针类型的偏特化
template<typename T>
struct MyClass<T *> {
    static void print() {
        cout << "print() for T*" << endl;
    }
};

// 根据语言规则，如果调用参数被声明为数组的话，那么它的真实类型是指针类型
template<typename T1, typename T2, typename T3>
void foo(int a1[7], int a2[], int (&a3)[42], int (&x0)[], T1 x1, T2 &x2, T3 &&x3) {
    MyClass<decltype(a1)>::print();
    MyClass<decltype(a2)>::print();
    MyClass<decltype(a3)>::print();
    MyClass<decltype(x0)>::print();
    MyClass<decltype(x1)>::print();
    MyClass<decltype(x2)>::print();
    MyClass<decltype(x3)>::print();
}

int main(int argc, char *argv[]) {

    // int x[] = {1, 2, 3};
    // int y[] = {1, 2, 3, 4, 5};
    // cout << boolalpha << ::less(x, y) << endl;
    // cout << boolalpha << ::less("abc", "abcd") << endl;

    int a[42];
    MyClass<decltype(a)>::print();
    extern int x[];
    MyClass<decltype(x)>::print();
    foo(a, a, a, x, x, x, x);

    return 0;
}

int x[] = {0, 8, 15};