//
// Created by suncx on 2022/12/5.
//

#include <deque>
#include <vector>
#include <iostream>

using namespace std;

// 第二个模板参数被定义为一个类模板
// 由于模板参数模板中的模板参数没有被用到，作为惯例可以省略它（本例中 E 可以被省略）
// 模板参数模板是类或者别名类（alias templates）的占位符，但是并没有与其对应的函数模板或者变量模板的占位符
template<typename T, template<typename E> class Cont = deque>
class Stack {
public:
    void push(const T &e);

    void pop();

    const T &top() const;

    inline bool empty() const {
        return m_elems.empty();
    }

private:
    // 用第一个模板参数实例化第二个模板参数的情况是由 Stack 自身的情况决定的。实际上，可以在类模板内部用任意类型实例化一个模板参数模板
    Cont<T> m_elems;
};

template<typename T, template<typename> class Cont>
void Stack<T, Cont>::push(const T &e) {
    m_elems.push_back(e);
}

// 模板参数模板的参数匹配
// 其中的 Alloc 同样可以被省略掉
template<typename T, template<typename E, typename Alloc = allocator<E>> class Cont = deque>
class Stack2 {
public:
    void push(const T &e);

    void pop();

    const T &top() const;

    inline bool empty() const {
        return m_elems.empty();
    }

    template<typename K, template<typename, typename> class ContK>
    Stack2<T, Cont> &operator=(const Stack2<K, ContK> &stack);

private:
    Cont<T> m_elems;

    template<typename, template<typename, typename> class> friend
    class Stack2;
};

template<typename T, template<typename, typename> class Cont>
void Stack2<T, Cont>::push(const T &e) {
    m_elems.push_back(e);
}

template<typename T, template<typename, typename> class Cont>
void Stack2<T, Cont>::pop() {
    m_elems.pop_back();
}

template<typename T, template<typename, typename> class Cont>
const T &Stack2<T, Cont>::top() const {
    return m_elems.back();
}

template<typename T, template<typename, typename> class Cont>
template<typename K, template<typename, typename> class ContK>
Stack2<T, Cont> &Stack2<T, Cont>::operator=(const Stack2<K, ContK> &stack) {
    m_elems.clear();
    m_elems.insert(m_elems.begin(), stack.m_elems.cbegin(), stack.m_elems.cend());
    return *this;
}

int main(int argc, char *argv[]) {

    // Stack<int, vector> s;
    Stack2<int, vector> iStack;
    Stack2<float, vector> fStack;

    iStack.push(1);
    iStack.push(2);
    cout << iStack.top() << endl;

    fStack.push(3.3);
    cout << fStack.top() << endl;

    fStack = iStack;
    fStack.push(4.4);
    cout << fStack.top() << endl;

    Stack2<double, vector> vStack;
    vStack.push(5.5);
    vStack.push(6.6);
    cout << vStack.top() << endl;

    vStack = fStack;
    cout << "vStack:" << endl;

    while (!vStack.empty()) {
        cout << vStack.top() << ' ';
        vStack.pop();
    }

    cout << endl;
    return 0;
}