//
// Created by suncx on 2022/12/2.
//

#include <array>
#include <iostream>
#include <vector>

using namespace std;

void print() {}

template<typename T, typename... Args>
void print(T arg, Args... args) {
    cout << arg << '\n';
    print(args...);
}

// 变参下标
template<typename T, typename... Idx>
void print_elems(const T &col, Idx... idx) {
    print(col[idx]...);
}

// 将非类型模板参数声明成参数包
template<size_t... idx, typename T>
void print_idx(const T &col) {
    print(col[idx]...);
}

template<size_t...>
struct Indices {
};

template<typename T, size_t... Idx>
void printByIdx(T v, Indices<Idx...>) {
    print(get<Idx>(v)...);
}

template<size_t ...>
class index_sequence {
};

template<size_t N>
using make_index_sequence = index_sequence<__integer_pack(N)...>;

template<size_t ... idx>
void print(index_sequence<idx...>) {
    size_t arr[] = {idx...};
    for (const auto e: arr) {
        cout << e << ' ';
    }
    cout << endl;
}

int main(int argc, char *argv[]) {

    // vector<string> v = {"good", "times", "say", "bye"};
    // print_elems(v, 2, 0, 3);
    // print_idx<2, 0, 3>(v);

    array<string, 5> arr = {"Hello", "my", "new", "!", "World"};
    printByIdx(arr, Indices<0, 4, 3>());

    print(make_index_sequence<6>());
    return 0;
}