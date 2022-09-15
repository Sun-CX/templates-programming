//
// Created by suncx on 2022/9/15.
//

#include <vector>
#include <deque>
#include <string>

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

// ------------------------------- 特化 -------------------------------
template<>
class Stack<std::string> {
public:
    void push(const std::string &s);

    void pop();

    const std::string &top() const;

    bool empty() const {
        return elems.empty();
    }

private:
    // 此处可以说明：模板类特例化之后的实现可能和模板类的原始实现有很大不同
    std::deque<std::string> elems;
};

// 对于被全特化的模板类，所有成员函数的定义都应该被定义成“常规”成员函数，也就是说所有出现 T 的地方，都应该被替换成用于特化类模板的类型
void Stack<std::string>::push(const std::string &s) {

}

void Stack<std::string>::pop() {

}

const std::string &Stack<std::string>::top() const {
    return elems.back();
}