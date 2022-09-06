add_executable(void-param void-param.cpp)
add_executable(two-phase-translation two-phase-translation.cpp)
add_executable(type-transfer-in-type-deduce type-transfer-in-type-deduce.cpp)
add_executable(default-param-in-function-template default-param-in-function-template.cpp)

find_package(Boost REQUIRED)
add_executable(multiple-template-args multiple-template-args.cpp)
target_link_libraries(multiple-template-args PRIVATE Boost::boost)