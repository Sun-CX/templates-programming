//
// Created by suncx on 2022/9/15.
//

/*
 * 非类型模板参数的限制：
 * 使用非类型模板参数是有限制的。通常它们只能是整形常量（包含枚举），指向 objects/functions/members 的指针，objects 或者 functions 的左值引用，
 * 或者是 std::nullptr_t（类型是 nullptr）
 *
 * 注意：浮点型数值或者 class 类型的对象都不能作为非类型模板参数使用
 * */

template<int VAL, typename T>
T add_value(T x) {
    return x + VAL;
}

// C++17
// 可以基于前面的非类型模板参数推断出当前模板参数的类型
template<auto VAL, typename T = decltype(VAL)>
T foo();

template<typename T, T VAL = T{}>
T bar();


template<const char *name>
class MyClass {

};

// ERROR: string literal "hello" not allowed
MyClass<"hello"> m1;

extern char const s03[] = "hi"; // external linkage
const char s11[] = "hi"; // internal linkage

int main(int argc, char *argv[]) {

    MyClass<s03> m03; // OK (all versions)
    MyClass<s11> m11; // OK since C++11

    static const char s17[] = "hi"; // no linkage
    MyClass<s17> m17; // OK since C++17

    return 0;
}

template<int X, bool Y>
class Foo {
};

// 非类型模板参数可以是任何编译期表达式
Foo<sizeof(int) + 4, sizeof(int) == 4> f1;

// 如果在表达式中使用了 operator >，就必须将相应表达式放在括号里，否则 > 会被作为模板参数列表末尾的 > 从而截断了参数列表
Foo<42, sizeof(int) > 4> f2; // Error: first > ends the template argument
Foo<42, (sizeof(int) > 4)> f3;
