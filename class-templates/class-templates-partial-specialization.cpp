//
// Created by suncx on 2022/9/15.
//

#include <vector>

template<typename T>
class Stack {
public:
    void push(const T &elem);

    void pop();

    const T &top() const;

    bool empty() const {
        return m_elems.empty();
    }

private:
    std::vector<T> m_elems;
};

// --------------------------- 从模板参数类型偏特化 ---------------------------
template<typename T>
class Stack<T *> {
public:
    void push(T *elem);

    // 注意：特化之后的函数接口可能不同
    T *pop();

    T *top() const;

    bool empty() const {
        return elems.empty();
    }

private:
    std::vector<T *> elems;
};

template<typename T>
void Stack<T *>::push(T *elem) {

}

template<typename T>
T *Stack<T *>::pop() {
    return nullptr;
}

template<typename T>
T *Stack<T *>::top() const {

}

// --------------------------- 多模板参数的部分特例化 ---------------------------
template<typename T1, typename T2>
class MyClass {
};

// partial specialization: both template parameters have same type
template<typename T>
class MyClass<T, T> {

};

// partial specialization: second type is int
template<typename T>
class MyClass<T, int> {

};

template<typename T1, typename T2>
class MyClass<T1 *, T2 *> {

};

// template<typename T>
// class MyClass<T *, T *> {
//
// };

MyClass<int, float> mif; // uses MyClass<T1,T2>
MyClass<float, float> mff; // uses MyClass<T,T>
MyClass<float, int> mfi; // uses MyClass<T,int>
MyClass<int *, float *> mp; // uses MyClass<T1*,T2*>

// ERROR: matches MyClass<T,T> and MyClass<T,int>
MyClass<int, int> m;

// ERROR: matches MyClass<T,T> and MyClass<T1*,T2*>
// 为了消除二义性，可以提供一个单独的特例化版本来处理相同类型的指针：MyClass<T*, T*>
MyClass<int *, int *> m1;
