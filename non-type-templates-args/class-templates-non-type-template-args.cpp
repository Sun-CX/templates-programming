//
// Created by suncx on 2022/9/15.
//

#include <cstddef>
#include <array>
#include <cassert>

template<typename T, std::size_t MaxSize>
class Stack {
public:
    Stack();

    void push(const T &elem);

    void pop();

    const T &top() const;

    bool empty() const {
        return num_elems == 0;
    }

    std::size_t size() const {
        return num_elems;
    }

private:
    std::array<T, MaxSize> elems;
    std::size_t num_elems;
};

template<typename T, std::size_t MaxSize>
Stack<T, MaxSize>::Stack(): elems(), num_elems(0) {

}

template<typename T, std::size_t MaxSize>
void Stack<T, MaxSize>::push(const T &elem) {
    assert(num_elems < MaxSize);
    elems[num_elems++] = elem;
}

template<typename T, std::size_t MaxSize>
void Stack<T, MaxSize>::pop() {
    assert(!empty());
    --num_elems;
}

template<typename T, std::size_t MaxSize>
const T &Stack<T, MaxSize>::top() const {
    assert(!empty());
    return elems[num_elems - 1];
}

Stack<int, 10> s1;
Stack<std::size_t, 100> s2;