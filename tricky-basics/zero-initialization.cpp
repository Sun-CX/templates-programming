//
// Created by suncx on 2022/12/2.
//

void foo() {
    int x;
    int *ptr;
}

template<typename T>
void foo() {
    // 对类型 T 进行默认初始化
    T x{};
}