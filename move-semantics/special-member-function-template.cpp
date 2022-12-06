//
// Created by suncx on 2022/12/6.
//

#include <iostream>
#include <boost/type_index.hpp>

using namespace std;
using namespace boost::typeindex;

class Person {
public:
    // 构造函数模板化会产生一个问题：
    // 根据 C++ 重载解析规则，对于一个非 const 左值的 Person p，成员模板
    // template<typename T>
    // Person(T&& name)
    // 通常比预定义的拷贝构造函数更匹配
    // template<typename T>
    // explicit Person(T &&name) : m_name(forward<T>(name)) {
    //     cout << "TMPL-CONSTR for " << m_name << endl;
    // }

    // 要解决上述问题，当参数是一个 Person 对象或者是一个可以转换成 Person 对象的表达式时，不要启用模板
    template<typename T, typename = typename enable_if<is_convertible<T, string>::value>::type>
    explicit Person(T &&name) : m_name(forward<T>(name)) {
        cout << type_id_with_cvr<T>().pretty_name() << endl;
        cout << type_id_with_cvr<decltype(name)>().pretty_name() << endl;
        cout << type_id_with_cvr<decltype(forward<T>(name))>().pretty_name() << endl;
        cout << "TMPL-CONSTR for " << m_name << endl;
    }

    // explicit Person(const string &name) : m_name(name) {
    //     cout << "copying string-CONSTR for " << m_name << endl;
    // }
    //
    // explicit Person(string &&name) : m_name(move(name)) {
    //     cout << "moving string-CONSTR for " << m_name << endl;
    // }

    Person(const Person &person) : m_name(person.m_name) {
        cout << "COPY-CONSTR Person " << m_name << endl;
    }

    Person(Person &&person) noexcept : m_name(move(person.m_name)) {
        cout << "MOVE-CONSTR Person " << m_name << endl;
    }

private:
    string m_name;
};

// ======================= 禁用某些成员函数 =======================
// 我们不能通过使用 enable_if<> 来禁用 copy/move 构造函数以及赋值构造函数
// 这是因为成员函数模板不会被算作特殊成员函数（依然会生成默认构造函数），而且在需要使用 copy 构造函数的地方，相应的成员函数模板会被忽略
class Foo {
public:
    Foo() = default;

    // Foo(const Foo &) = delete;
    Foo(const volatile Foo &) = delete;

    template<typename T>
    explicit Foo(const T &) {
        cout << "tmpl copy constructor" << endl;
    }
};

template<typename T>
class Foo2 {
public:
    Foo2() = default;

    Foo2(const volatile Foo2 &) = delete;

    template<typename U, typename = typename enable_if<!is_integral<U>::value>::type>
    explicit Foo2(const Foo2<U> &) {

    }
};

int main(int argc, char *argv[]) {

    string s = "sname";

    Person p1(s);
    Person p2("tmp");

    // Person p3(p1);
    // const Person p2c("ctmp");
    // Person p3c(p2c);

    // Person p4(move(p1));

    Foo x;
    // 依然会调用预定义的拷贝构造函数，而不是成员函数模板
    // 删除拷贝构造函数也不行，因为这样在需要拷贝构造函数的地方会报错说该函数被删除了
    // 有一个办法：可以定义一个接受 const volatile 的拷贝构造函数并将其标示为 delete
    // 这样做就不会再隐式声明一个接受 const 参数的拷贝构造函数。在此基础上，可以定义一个构造函数模板，对于 non-volatile 的类型，它会优先被选择（相较于已删除的拷贝构造函数）
    Foo y(x);

    Foo2<int> f2;
    Foo2<double> fd;
    Foo2<string> fs(f2);
    Foo2<string> fss(fd);

    return 0;
}