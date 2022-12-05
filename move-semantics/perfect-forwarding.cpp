//
// Created by suncx on 2022/12/5.
//

#include <iostream>

using namespace std;

class X {

};

void g(X &) {
    cout << "g() for variable" << endl;
}

void g(const X &) {
    cout << "g() for constant" << endl;
}

void g(X &&) {
    cout << "g() for movable" << endl;
}

// void f(X &val) {
//     g(val);
// }
//
// void f(const X &val) {
//     g(val);
// }
//
// // Note: val 虽然是一个右值引用，但是 val 本身依然是一个非常量左值
// void f(X &&val) {
//     g(move(val));
// }

// 实现完美转发这一目的的惯用方法，以代替上面三种 f() 的不同重载
template<typename T>
void f(T &&val) {
    g(forward<T>(val));
}

int main(int argc, char *argv[]) {
    X v;
    const X c;
    f(v);
    f(c);
    f(X());
    f(move(v));

    return 0;
}