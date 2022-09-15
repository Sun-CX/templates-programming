//
// Created by suncx on 2022/9/15.
//

#include <vector>
#include <deque>

template<typename T, typename Container = std::vector<T>>
class Stack {
public:
    void push(const T &elem);

    void pop();

    const T &top() const;

    bool empty() const {
        return elems.empty();
    }

private:
    Container elems;
};

template<typename T, typename Container>
void Stack<T, Container>::push(const T &elem) {}

template<typename T, typename Container>
void Stack<T, Container>::pop() {}

template<typename T, typename Container>
const T &Stack<T, Container>::top() const {}

// ------------------------------------- 别名模板 -------------------------------------
template<typename T>
using DequeStack = Stack<T, std::deque<T>>;

// ------------------------------------- 使用 -------------------------------------
Stack<int> int_stack; // int stack using std::vector<int>
Stack<double, std::deque<double>> double_stack; // double stack using std::deque<double>