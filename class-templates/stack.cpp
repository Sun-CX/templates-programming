//
// Created by suncx on 2022/9/15.
//

#ifndef STACK_H
#define STACK_H

#include <vector>
#include <string>
#include <cassert>
#include <iostream>

template<typename T>
class Stack {
public:
    // --------------------------------------------------------------------
    Stack(const Stack &stack);

    Stack &operator=(const Stack &stack);

    Stack(const Stack<T> &stack);

    Stack<T> &operator=(const Stack<T> &stack);
    // 一般 <T> 暗示要对某些模板参数做特殊处理，所以最好还是使用第一种方式
    // 这两种写法是等价的，但推荐使用第一种写法
    // --------------------------------------------------------------------

    void push(const T &elem);

    void pop();

    const T &top() const;

    bool empty() const {
        return elems.empty();
    }

    void printOn(std::ostream &os) const {
        for (const T &e: elems) {
            os << e << ' ';
        }
    }

    // 注意：这里的 operator<< 并不是一个函数模板（对于在模板类内定义这一情况），而是在需要的时候，随类模板实例化出来的一个常规函数
    // friend std::ostream &operator<<(std::ostream &os, const Stack<T> &stack) {
    //     stack.printOn(os);
    //     return os;
    // }

    // 如果先在类内声明一个友元函数，然后在类外去定义它，那么情况变得非常复杂
    // 选择一：类内的声明实际上是多余的，可以只在类外定义即可
    // 无论是继续使用 T 还是省略掉模板参数声明，都不可以（要么是里面的 T 隐藏了外面的 T，要么是在命名空间作用域内声明了一个非模板函数）
    // template<typename U>
    // friend std::ostream &operator<<(std::ostream &os, const Stack<U> &s);

    // 选择二：没搞懂
    // template<typename T>
    // class Stack;
    // template<typename T>
    // std::ostream &operator<<(std::ostream &os, const Stack<T> &s);

    friend std::ostream &operator<<<T>(std::ostream &os, const Stack<T> &s);

private:
    std::vector<T> elems;
    static_assert(std::is_default_constructible<T>::value, "Stack<T> requires default-constructible elements.");
};

// 定义类模板的成员函数时，必须指出它是一个模板，也必须使用该类模板的所有类型限制
template<typename T>
void Stack<T>::push(const T &elem) {
    elems.push_back(elem);
}

template<typename T>
void Stack<T>::pop() {
    assert(!empty());
    elems.pop_back();
}

template<typename T>
const T &Stack<T>::top() const {
    assert(!empty());
    return elems.back();
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &stack) {
    return *this;
}

// 但如果定义在类模板的外面，则一律需要加 <T>
// Note: 在只需要类的名字而不是类型的地方，可以只用 Stack，即不需要带 <T>
template<typename T>
bool operator==(const Stack<T> &lhs, const Stack<T> &rhs) {
    return false;
}

// template<typename U>
// std::ostream &operator<<(std::ostream &os, const Stack<U> &s) {
//     return os;
// }

template<typename T>
class Stack;

template<typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s) {
    return os;
}

class Foo {
public:
    Foo() = delete;
};

int main(int argc, char *argv[]) {
    Stack<int> intStack;
    Stack<std::string> stringStack;

    std::cout << intStack;

    Stack<Foo> fooStack;

    // 部分地使用类模板：
    // 模板参数只需要提供那些会被用到的操作：std::pair 没有提供 << 运算符，但仍然可以使用 push 操作
    // 根本原因是：模板函数和模板成员函数只有在被调用的时候才会实例化
    Stack<std::pair<int, int>> ps;
    ps.push({4, 5});
    ps.push({6, 7});

    ps.printOn(std::cout);

    return 0;
}

#endif //STACK_H
