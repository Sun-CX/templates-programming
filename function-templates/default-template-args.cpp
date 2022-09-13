//
// Created by suncx on 2022/9/13.
//

#include <type_traits>

// 值得注意的是，这一实现方式要求我们能够调用两个模板参数的默认构造函数
// 还有另一种方法，使用 std::declval，不过这将使得声明部分变得更加复杂。后续再详细解释
template<typename T1, typename T2, typename RT = typename std::decay<decltype(true ? T1() : T2())>::type>
RT max(T1 x, T2 y) {
    return x < y ? y : x;
}

// 也可以利用类型萃取 std::common_type<> 作为返回类型的默认值
template<typename T1, typename T2, typename RT = typename std::common_type<T1, T2>::type>
RT max_common(T1 x, T2 y) {
    return x < y ? y : x;
}

/* 上面的两种实现方式会有这样一个问题：
 *    为了显式指出返回类型，我们必须显式的指出全部三个模板参数的类型。
 *    因此我们希望能够将返回类型作为第一个模板参数，并且依然能够从其它两个模板参数推断出它的类型。
 *    原则上这是可行的：只有当模板参数具有一个“天生的”默认值时，这才有意义。
 * */
template<typename RT = long, typename T1, typename T2>
RT max_rt(T1 x, T2 y) {
    return x < y ? y : x;
}

int main(int argc, char *argv[]) {


    return 0;
}