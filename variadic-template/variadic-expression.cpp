//
// Created by suncx on 2022/12/2.
//

#include <iostream>

using namespace std;

void print() {}

template<typename T, typename ...Args>
void print(T arg, Args... args) {
    cout << arg << '\n';
    print(args...);
}

// since C++11
// 将参数包中所有的参数翻倍，然后将结果传给 print()
template<typename ...T>
void doubled_print(T ... args) {
    print(args + args...);
}

// since C++11
// 将参数包中所有的参数加 1
template<typename ...T>
void add_one(T ... args) {
    // 数字 1 后面必须跟个空格，再接 ...
    print(args + 1 ...);
    // 或者用括号扩起来，后再接 ...
    // print((args + 1)...);
}

// since C++17
// 判断所有参数包中参数的类型是否相同
template<typename T, typename ... Ts>
constexpr bool is_homogeneous(T, Ts...) {
    return (is_same<T, Ts>::value and ...);
}

int main(int argc, char *argv[]) {

    string s = "world";
    // doubled_print(1, s, 3.14);
    add_one(1, 3.14);

    static_assert(is_homogeneous("hello", "", "world", "!"));

    return 0;
}