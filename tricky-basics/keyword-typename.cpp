//
// Created by suncx on 2022/12/2.
//

#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class MyClass {
public:
    void foo() {
        // 当一个依赖于模板参数的名称代表的是某种类型的时候，就必须使用 typename
        typename T::SubType *ptr;
    }
};

template<typename T>
void print(const T &col) {
    typename T::const_iterator pos;
    typename T::const_iterator end = col.cend();
    for (pos = col.cbegin(); pos != end; ++pos) {
        cout << *pos << '\n';
    }
    cout << endl;
}

int main(int argc, char *argv[]) {

    vector<int> v = {1, 2, 3, 4, 5};
    print(v);
}