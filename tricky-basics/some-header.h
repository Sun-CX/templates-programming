//
// Created by suncx on 2022/12/5.
//

#ifndef TEMPLATES_PROGRAMMING_SOME_HEADER_H
#define TEMPLATES_PROGRAMMING_SOME_HEADER_H

#include <iostream>

template<typename T>
T val{};

void print() {
    std::cout << val<long> << std::endl;
}

#endif //TEMPLATES_PROGRAMMING_SOME_HEADER_H
