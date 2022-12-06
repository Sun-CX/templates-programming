find_package(Boost REQUIRED)
add_executable(pass-arguments pass-arguments.cpp)
target_link_libraries(pass-arguments PRIVATE Boost::boost)