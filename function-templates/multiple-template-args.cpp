//
// Created by suncx on 2022/9/6.
//

#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using namespace boost::typeindex;

template<typename T1, typename T2, typename RT>
RT max(T1 x, T2 y) {
    return x < y ? y : x;
}

template<typename RT, typename T1, typename T2>
RT max_optimized_1(T1 x, T2 y) {
    return x < y ? y : x;
}

// C++14 支持
// 如果返回类型是由模板参数决定的，那么推断返回类型最简单也是最好的办法就是让编译器来做这件事
#if __cplusplus >= 201402L

template<typename T1, typename T2>
auto max_optimized_cpp14(T1 x, T2 y) {
    cout << type_id_with_cvr<decltype(x < y ? y : x)>().pretty_name() << endl;
    return x < y ? y : x;
}

#endif

/* ---------------------------------------------------------------------------------------- */
// 下面的 C++11 风格的写法在某些情况下会有一个严重的问题：由于 T 可能是引用类型，返回类型就也就可能被推断为引用类型。
// 一旦被推断为引用类型，那么就返回了一个栈上变量的引用，导致内存问题！！！
// 因此需要退化为值类型
#define DECLARE_TYPE_STYLE 1

#if DECLARE_TYPE_STYLE

// C++11 style
template<typename T1, typename T2>
auto max_optimized_cpp11(T1 x, T2 y) -> decltype(x < y ? y : x) {
    cout << type_id_with_cvr<T1>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(x)>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(x < y ? y : x)>().pretty_name() << endl;
    return x < y ? y : x;
}

#else

// C++11 style
// 事实上用 true 作为运算符 ?: 的条件就足够了
// auto max_optimized_cpp11(T1 x, T2 y) -> decltype(true ? x : y);
template<typename T1, typename T2>
auto max_optimized_cpp11(T1 x, T2 y) -> decltype(true ? x : y) {
    cout << type_id_with_cvr<T1>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(x)>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(true ? x : y)>().pretty_name() << endl;
    return x < y ? y : x;
}

#endif

// decay 后的版本
template<typename T1, typename T2>
auto max_optimized_cpp11_decay(T1 x, T2 y) -> typename std::decay<decltype(true ? x : y)>::type {
    cout << type_id_with_cvr<typename std::decay<decltype(true ? x : y)>::type>().pretty_name() << endl;
    return x < y ? y : x;
}

// 公共类型的版本
// 需要注意的是，std::common_type<> 的结果也是退化的
template<typename T1, typename T2>
typename std::common_type<T1, T2>::type max_optimized_cpp11_common_type(T1 x, T2 y) {
    cout << type_id_with_cvr<typename std::common_type<T1, T2>::type>().pretty_name() << endl;
    return x < y ? y : x;
}

/* ---------------------------------------------------------------------------------------- */


int main(int argc, char *argv[]) {

    // 模板类型推断不会考虑返回值类型，因此第三个参数 RT 的类型不会被推断。必须显式的指明模板参数的类型
    // OK, 但是太繁琐
    auto val1 = max<int, int, long>(1, 2);

    // 改变模板参数顺序，只需指明第一个模板参数，后续的参数通过类型推断
    // 可见模板参数的顺序很考究
    auto val2 = max_optimized_1<double>(1, 2);

    int x = 1, y = 2;
    const int &rx = x, &ry = y;
#if __cplusplus >= 201103L && __cplusplus < 201402L
    // auto v1 = max_optimized_cpp11(rx, ry);
    // auto v = max_optimized_cpp11_decay(rx, ry);
    auto vv = max_optimized_cpp11_common_type(rx, ry);
#else
    auto v2 = max_optimized_cpp14(rx, ry);
#endif

    return 0;
}