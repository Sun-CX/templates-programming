//
// Created by 孙诚雄 on 2022/8/23.
//

#include <string>

template<typename T>
void foo(T = "") {}

/*
 * 如果函数模版有默认参数，那么也需要给模板类型参数也声明一个默认参数
 * */
template<typename T = std::string>
void bar(T = "") {}

int main(int argc, char *argv[]) {
    foo(1); // T 被推断为 int，调用 foo<int>(i)

    foo(); // ERROR: 无法推断 T 的类型

    bar(); // OK
    return 0;
}