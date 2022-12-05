//
// Created by suncx on 2022/12/2.
//

void foo() {
    int x;
    int *ptr;
}

template<typename T>
void foo() {
    // 这种初始化的方法被称为“值初始化（value
    // initialization）”，它要么调用一个对象已有的构造函数，要么就用零来初始化这个对象。即使它有显式的构造函数也是这样。
    // 对类型 T 进行默认初始化
    T x{};
}

// since C++11
// 对默认参数使用这一方式初始化
template<typename T>
void foo(T x = T{}) {
}