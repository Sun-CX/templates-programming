//
// Created by suncx on 2022/9/13.
//

#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using namespace boost::typeindex;

// 一个非模板函数可以和一个与其同名的函数模板共存
int max(int x, int y) {
    return x < y ? y : x;
}

template<typename T>
T max(T x, T y) {
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    return x < y ? y : x;
}

// --------------------------------- interesting example 1 ---------------------------------
template<typename T1, typename T2>
typename std::common_type<T1, T2>::type max_i(T1 x, T2 y) {
    return x < y ? y : x;
}

template<typename RT, typename T1, typename T2>
RT max_i(T1 x, T2 y) {
    return x < y ? y : x;
}

// --------------------------------- interesting example 2 ---------------------------------
template<typename T>
T *max(T *x, T *y) {
    return *x < *y ? y : x;
}

const char *max(const char *x, const char *y) {
    return std::strcmp(x, y) < 0 ? y : x;
}

int main(int argc, char *argv[]) {

    /* 一个非模板函数可以和一个与其同名的函数模板共存，并且这个同名的函数模板
     * 可以被实例化为与非模板函数具有相同类型的调用参数。在所有其它因素都相同的情况
     * 下，模板解析过程将优先选择非模板函数，而不是从模板实例化出来的函数 */
    ::max(7, 42); // 调用非模板函数

    /* 如果模板可以实例化出一个更匹配的函数，那么就会选择这个模板 */
    ::max(7.0, 42.0); // 参数推断，调用 max<double>
    ::max('a', 'b'); // 参数推断，调用 max<char>

    /* 可以显式指定一个空的模板列表。这表明它会被解析成一个模板调用，其所有的模板参数会通过调用参数推断出来 */
    ::max<>(7, 42); // 参数推断，调用 max<int>

    ::max<double>(7, 42); // 调用 max<double>，没有参数推断

    /* 模板参数推断时不允许自动类型转换，而常规函数是允许的 */
    ::max('a', 42.7); // 调用非模板函数


    auto a = max_i(4, 7.2);
    auto b = max_i<long double>(7.2, 4);
    // ERROR: ambiguous call: both function templates match
    auto c = max_i<int>(4, 7.2);

    // --------------------------------------------------------
    int x = 7, y = 42;
    auto m1 = ::max(x, y); // 调用非模板函数

    std::string s1 = "hey", s2 = "you";
    auto m2 = ::max(s1, s2); // 调用 max<std::string>

    int *p1 = &y, *p2 = &x;
    auto m3 = ::max(p1, p2); // 调用 max<T *, T *> 函数模板

    const char *hx = "hello";
    const char *hy = "world";

    auto m4 = ::max(hx, hy); // 调用 max<const char *, const char *> 函数模板

    return 0;
}