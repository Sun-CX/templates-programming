//
// Created by suncx on 2022/12/5.
//

template<typename T>
class Base {
public:
    void bar() {

    }
};

template<typename T>
class Derived : public Base<T> {
public:
    void foo() {
        // 永远不会被解析成 Base 中的 bar()
        // 这样做要么会遇到错误，要么就是调用了其它地方的 bar()，比如可能是定义在其它地方的 global 的 bar()
        bar();
        // 作为经验法则，建议当使用定义于基类中的、依赖于模板参数的成员时，用 this-> 或者 Base<T>:: 来修饰
        this->bar();
    }
};