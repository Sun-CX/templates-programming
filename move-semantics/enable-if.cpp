//
// Created by suncx on 2022/12/6.
//

#include <type_traits>

// since C++11
template<typename T>
typename std::enable_if<(sizeof(T) > 4)>::type foo(T x) {

}

// since C++14
template<typename T>
std::enable_if_t<(sizeof(T) > 4)> foo() {

}

// 将 enable_if 表达式放在声明的中间不是一个明智的做法，因此使用 std::enable_if<> 的更常见的方法是使用一个额外的、有默认值的模板参数
template<typename T, typename = typename std::enable_if<(sizeof(T) > 4)>::type>
void foo1() {}

int main(int argc, char *argv[]) {


    return 0;
}