//
// Created by 孙诚雄 on 2022/8/23.
//

#include <string>

/*
 * 类型推断中的类型转换:
 *  1 如果调用参数是按引用传递的，那么任何类型转换都不被允许
 *  2 如果调用参数是按值传递的，那么只有退化(decay)这一类简单转换是被允许的:
 *      const 和 volatile 限制符会被忽略，
 *      引用被转换成被引用的类型，
 *      raw array 和函数被转换为相应的指针类型。
 *      通过模板类型参数 T 定义的两个参数，它们实参的类型在退化(decay) 后必须相同
 * */
template<typename T>
T max(T x, T y) {
    return x < y ? y : x;
}

int main(int argc, char *argv[]) {

    const int c = 42;
    int i = 1;
    max(i, c); // T 推断为 int，c 的 const 被 decay 掉了

    int &ri = i;
    max(i, ri); // T 推断为 int，ri 的引用被 decay 掉了

    int arr[4];
    max(&i, arr); // T 推断为 int *，arr 被 decay 为 int *


    // =====================================================
    max(4, 7.2); // ERROR: 不确定 T 该被推断为 int 还是 double
    std::string s;
    max("hello", s); // ERROR: 不确定 T 该被推断为 const char[6] 还是 std::string

    // 解决办法：
    max(static_cast<double>(4), 7.2); // 强行将类型转换一致
    max<double>(4, 7.2); // 显式的指明类型参数 T 的类型，这样编译器就不再会去做类型推导

    return 0;
}