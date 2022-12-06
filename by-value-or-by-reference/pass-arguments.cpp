//
// Created by suncx on 2022/12/6.
//

#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using namespace boost::typeindex;

template<typename T>
void printV(T arg) {
    cout << type_id_with_cvr<T>().pretty_name() << endl;
}

template<typename T>
void printR(const T &arg) {}

// 如果传递的参数是 const 的，arg 的类型就有可能被推断为 const 引用，也就是说这时可以传递一个右值（rvalue）作为参数，但是模板所期望的参数类型却是左值
// 在这种情况下，在函数模板内部，任何试图更改被传递参数的值的行为都是错误的
// 如果想禁止非 const 引用传递 const 对象，有如下选择: 1. static_assert 2. enable_if
template<typename T>
void outR(T &arg) {
    static_assert(!is_const<T>::value, "");
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(arg)>().pretty_name() << endl;
}

template<typename T, typename = typename enable_if<!is_const<T>::value>::type>
void outR1(T &arg) {}

template<typename T>
void passR(T &&arg) {
    cout << type_id_with_cvr<T>().pretty_name() << endl;
    cout << type_id_with_cvr<decltype(arg)>().pretty_name() << endl;
}

string return_string() {
    return "hello";
}

const string return_const_string() {
    return "hello";
}

void print_string(const string &s) {
    cout << s << endl;
}

template<typename T>
void print(T arg) {
    print_string(arg);
}

int main(int argc, char *argv[]) {

    // string s = "hi";
    // printV(s); // 拷贝 s
    // printV(string("hi")); // 通常拷贝会被优化掉，如果没有，用 move
    // printV(return_string()); // 通常拷贝会被优化掉，如果没有，用 move
    // printV(move(s)); // 移动构造
    //
    // string s1 = "hi";
    // printR(s1);
    // printR(string("hi"));
    // printR(return_string());
    // printR(move(s1)); // const string & 接收了一个右值，会导致移动失败
    //
    // cout << s1 << endl;
    //
    // string s3 = "hi";
    // outR(s3);
    // outR(string("hi"));
    // outR(return_string());
    // outR(move(s3));
    // int arr[4];
    // outR(arr);
    //
    // const string s4 = "hi";
    // outR(s4);
    // outR(return_const_string());
    // outR(move(s4));
    // outR("hi");
    //
    // outR1(return_const_string());

    // string s5 = "hi";
    // passR(s5);
    // passR(string("hi"));
    // passR(move(s5));
    // char ac[5];
    // passR(ac);
    // const string s5c = "hi";
    // passR(s5c);
    // passR("hi");
    // passR(42);

    string s6 = "hi";
    print(s6);
    print(cref(s6));

    cout << sizeof(reference_wrapper<string>) << endl;

    return 0;
}