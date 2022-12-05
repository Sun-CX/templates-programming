//
// Created by suncx on 2022/12/5.
//

#include <deque>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class Stack {
public:
    void push(const T &e);

    void pop();

    const T &top() const;

    inline bool empty() const {
        return m_elems.empty();
    }

    template<typename K>
    Stack &operator=(const Stack<K> &stack);

private:
    deque<T> m_elems;

    template<typename> friend
    class Stack;
};

// 由于 Stack<T> 与 Stack<K> 是不同的类型，所以在此函数内部，不能访问参数 stack 的私有成员变量 m_elems
// 要想解决这个问题，可以将其它所有类型的 stack 模板的实例都定义成友元
// template<typename T>
// template<typename K>
// Stack<T> &Stack<T>::operator=(const Stack<K> &stack) {
//     Stack<K> tmp(stack);
//     m_elems.clear();
//     while (!tmp.empty()) {
//         m_elems.push_front(tmp.top());
//         tmp.pop();
//     }
//     return *this;
// }

template<typename T>
template<typename K>
Stack<T> &Stack<T>::operator=(const Stack<K> &stack) {
    m_elems.clear();
    m_elems.insert(m_elems.begin(), stack.m_elems.cbegin(), stack.m_elems.cend());
    return *this;
}

// 除了将容器的元素类型参数化，容器类型也可以参数化
template<typename T, typename Cont = deque<T>>
class Stack2 {
public:
    void push(const T &e);

    void pop();

    const T &top() const;

    inline bool empty() const {
        return m_elems.empty();
    }

    template<typename K, typename Cont2>
    Stack2 &operator=(const Stack2<K, Cont2> &stack);

private:
    Cont m_elems;

    template<typename, typename> friend
    class Stack2;
};

template<typename T, typename Cont>
template<typename K, typename Cont2>
Stack2<T, Cont> &Stack2<T, Cont>::operator=(const Stack2<K, Cont2> &stack) {
    m_elems.clear();
    m_elems.insert(m_elems.begin(), stack.m_elems.cbegin(), stack.m_elems.cend());
    return *this;
}

// ============================= 成员模板的特例化 =============================
// 成员函数模板也可以被全部或者部分地特例化
class BoolString {
public:
    explicit BoolString(string s) : m_value(move(s)) {}

    template<typename T = string>
    T get() const {
        return m_value;
    }

private:
    string m_value;
};

// 成员函数模板的全特化
template<>
inline bool BoolString::get() const {
    return m_value == "true" or m_value == "1" or m_value == "on";
}

int main(int argc, char *argv[]) {
    // Stack<int> intStack1, intStack2;
    // Stack<float> floatStack1, floatStack2;
    // intStack1 = intStack2;
    // 两个栈具有不同的类型，必须用模板重写赋值运算符
    // Note: 构造函数模板或者赋值运算符模板不会取代预定义的构造函数和赋值运算符
    //       成员函数模板不会被算作用来 copy 或者 move 对象的特殊成员函数。在上面的例子中，如果在相同类型的 stack 之间相互赋值，调用的依然是默认赋值运算符
    // floatStack1 = intStack1;

    Stack2<int, vector<int>> s2;

    BoolString s("on1");
    cout << boolalpha << s.get<bool>() << endl;

    return 0;
}