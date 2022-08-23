//
// Created by 孙诚雄 on 2022/8/23.
//
/*
 * 两阶段检查：
 * 在模板定义阶段，模板的检查不包含类型参数的检查。只包含下面几个方面：
 *  1 语法检查，比如少了分号；
 *  2 使用了未定义的不依赖于模板参数的名称(类型名，函数名，......)，会直接报错
 *  3 未使用模板参数的 static assertions
 *
 * 在模板实例化阶段，为确保所有代码都是有效的，模板会再次被检查，尤其是那些依赖于类型参数的部分
 *
 * Note:
 *  需要注意的是，有些编译器并不会执行第一阶段中的所有检查；
 *  因此如果模板没有被至少实例化一次的话，可能一直都不会发现代码中的常规错误
 * */

#include <complex>

using std::complex;

template<typename T>
T max(T x, T y) {
    return x < y ? y : x;
}

int main(int argc, char *argv[]) {

    complex<float> c1, c2;
    // std::complex 不支持比较运算符
    // 但是报错不会出现在调用处，而是在被调用处：模版定义处
    auto value = ::max(c1, c2);

    return 0;
}

template<typename T>
void foo(T x) {
    undeclared(); // 不依赖模版参数 x，第一阶段就会报错

    undeclared(x); // 依赖模版参数 x，第二阶段报错

    static_assert(sizeof(int) > 10, ""); // 不依赖模版参数 x 的静态断言，第一阶段就会报错

    static_assert(sizeof(x) > 10, ""); // 依赖模版参数 x 的静态断言，与模板参数有关，只会在第二阶段报错
}