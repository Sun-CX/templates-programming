find_package(Boost REQUIRED)

add_executable(perfect-forwarding perfect-forwarding.cpp)
add_executable(special-member-function-template special-member-function-template.cpp)
target_link_libraries(special-member-function-template PRIVATE Boost::boost)

set(CMAKE_CXX_STANDARD 14)
add_executable(enable-if enable-if.cpp)