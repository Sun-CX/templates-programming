//
// Created by suncx on 2022/9/15.
//

#include <array>
#include <type_traits>
#include <iostream>

// C++ 17 开始支持
template<typename T, auto MaxSize>
class Stack {
public:
    // 可以使用 MaxSize 的类型
    using size_type = decltype(MaxSize);

    Stack();

    void push(const T &elem);

    void pop();

    const T &top() const;

    bool empty() const {
        return num_elems == 0;
    }

    // 可以使用 MaxSize 的类型，还可以将它用于成员函数 size() 的返回类型
    size_type size() const {
        return num_elems;
    }

    // 从 C++14 开始，也可以通过使用 auto，让编译器推断出具体的返回类型
    auto size2() const {
        return num_elems;
    }

private:
    // 在模板内部，既可以使用 MaxSize 的值
    std::array<T, MaxSize> elems;
    size_type num_elems;
};

template<typename T, auto MaxSize>
Stack<T, MaxSize>::Stack():elems(), num_elems(0) {}

template<typename T, auto MaxSize>
void Stack<T, MaxSize>::push(const T &elem) {

}

template<typename T, auto MaxSize>
void Stack<T, MaxSize>::pop() {}

template<typename T, auto MaxSize>
const T &Stack<T, MaxSize>::top() const {}

int main(int argc, char *argv[]) {

    Stack<int, 20u> int20stack;

    Stack<std::string, 40> string_stack;

    auto size1 = int20stack.size();

    auto size2 = string_stack.size();

    if (!std::is_same<decltype(size1), decltype(size2)>::value) {
        std::cout << "size types differ." << std::endl;
    }

    // 从 C++17 开始，对于返回类型的类型萃取，可以通过使用下标 _v 省略掉::value
    if (!std::is_same_v<decltype(size1), decltype(size2)>) {
        std::cout << "size types differ." << std::endl;
    }

    return 0;
}

// 可以使用 template<decltype(auto)>，这样可以将 N 实例化成引用类型
template<decltype(auto) N>
class Foo {
};

int x;
// 注意：x 的括号不能省略
Foo<(x)> foo; // N is int& type