//
// Created by suncx on 2022/12/2.
//

#include <iostream>
#include <cassert>

using namespace std;

// 折叠表达式属于 C++ 17 的新特性
template<typename... T>
auto fold_sum(T... args) {
    // 注意这个括号是必不可少的
    return (... + args);
}

// 折叠表达式遍历一棵二叉树的路径
struct Node {
    int value;
    Node *left;
    Node *right;

    explicit Node(int i = 0) : value(i), left(nullptr), right(nullptr) {}
};

template<typename T, typename ...Ts>
Node *traverse(T np, Ts... paths) {
    return (np ->* ... ->*paths);
}

// 使用折叠表达式打印变参模板参数
template<typename ...T>
void print(T ... args) {
    (cout << ... << args) << '\n';
}

// 追加空格
template<typename T>
class AddSpace {
public:
    explicit AddSpace(const T &r) : ref(r) {}

    friend ostream &operator<<(ostream &os, AddSpace<T> s) {
        return os << s.ref << ' ';
    }

private:
    const T &ref;
};

template<typename ...T>
void print1(T ... args) {
    (cout << ... << AddSpace<T>(args)) << '\n';
}

int main(int argc, char *argv[]) {
    // auto sum = fold_sum();
    // cout << sum << endl;

    // Node *root = new Node(0);
    // root->left = new Node(1);
    // root->left->right = new Node(2);
    //
    // // 类成员指针
    // auto g_left = &Node::left;
    // auto g_right = &Node::right;
    // Node *node = traverse(root, g_left, g_right);
    // assert(node == root->left->right);
    //
    // delete root->left->right;
    // delete root->left;
    // delete root;

    string s = "world";
    print(1, "hello", s, 3.14);
    print1(1, "hello", s, 3.14);

    return 0;
}