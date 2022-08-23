//
// Created by 孙诚雄 on 2022/8/23.
//
/*
 * void 也可以作为模版类型参数
 * */
template<typename T>
void foo(T *) {}

int main(int argc, char *argv[]) {

    void *ptr = nullptr;
    foo(ptr);
    foo<void>(ptr);

    int *pin = nullptr;
    foo(pin);
    foo<void>(pin);

    return 0;
}