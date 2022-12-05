//
// Created by suncx on 2022/12/5.
//

#include "some-header.h"
#include <array>

using namespace std;

// since C++14
template<typename T>
constexpr T pi{3.14};

// 变量模板也可有默认模板类型
template<typename T = long double>
constexpr T dp{3.1415926535897932385};

template<size_t N>
array<int, N> arr{};

// since C++17
template<auto N>
constexpr decltype(N) dval{N};

// ================================== 用于数据成员的变量模板 ==================================
template<typename T>
class MyClass {
public:
    static constexpr int max = 1000;
};

// since C++14
template<typename T>
int my_max = MyClass<T>::max;

int main(int argc, char *argv[]) {

    cout << pi<float> << endl;
    cout << pi<double> << endl;

    // 变量模板可用于不同的编译单元
    val<long> = 42;
    print();

    // 无论怎样都要使用 <>，不能省略
    cout << dp<> << endl;
    cout << dp<float> << endl;

    cout << dval<'c'> << endl;
    arr<10>[0] = 42;

    for (size_t i = 0; i < arr<10>.size(); ++i)
        cout << arr<10>[i] << endl;

    auto max = my_max<string>;
    cout << max << endl;

    return 0;
}