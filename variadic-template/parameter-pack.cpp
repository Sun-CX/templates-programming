//
// Created by suncx on 2022/12/2.
//

#include <iostream>

using namespace std;

// ===================== 典型的变参模板的参数展开方法 =====================
void print() {
    cout << "empty args." << endl;
}

template<typename T, typename ...Args>
void print(T arg, Args... args) {
    // args 是一个函数参数包
    cout << arg << '\n';
    print(args...);
}

// ============= 上面的例子也可以这样实现 =============
// 当两个函数模板的区别只在于尾部的参数包时，会优先选择没有尾部参数包的那一个函数模板
template<typename T>
void print1(T arg) {
    cout << "one param: " << arg << '\n';
}

template<typename T, typename... Args>
void print1(T arg, Args... args) {
    cout << "template." << '\n';
    print1(arg);
    print1(args...);
}

// ===================== sizeof... 运算符 =====================
// 运算符 sizeof.. 既可以用于模板参数包，也可以用于函数参数包
template<typename T, typename ... Args>
void print2(T arg, Args... args) {
    cout << arg << '\n';
    cout << sizeof...(Args) << '\n';
    cout << sizeof...(args) << '\n';
}

// ========== 错误案例 ==========
// if 判断是运行时决定的，而是否实例化代码是在编译期决定的，所以在编译期 print3() 也会被实例化，但没有定义它们，所以会报错
// C++ 17 可以用特殊的语法来实现此例想要实现的功能
template<typename T, typename ... Args>
void print3(T arg, Args ... args) {
    cout << arg << '\n';
    if (sizeof...(args) > 0)
        print3(args...);
}

int main(int argc, char *argv[]) {

    string s = "world";
    // print(1, "hello", s, 3.14);
    // print1(1, "hello", s, 3.14);
    print2(1, "hello", 1.2, 3.14);
    // print3(1, "hello", s, 3.14);
    return 0;
}