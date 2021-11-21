cmake_minimum_required(VERSION 2.8.3)
project(Threading)

##查找头文件
find_package(Threads REQUIRED)



add_executable(t1  src/t1.cpp)
target_link_libraries(t1 PRIVATE Threads::Threads)

add_executable(t2  src/t2.cpp)
target_link_libraries(t2 PRIVATE Threads::Threads)

add_executable(t4  src/t4.cpp)
target_link_libraries(t4 PRIVATE Threads::Threads)

add_executable(t6  src/t6.cpp)
target_link_libraries(t6 PRIVATE Threads::Threads)

add_executable(t7  src/t7.cpp)
target_link_libraries(t7 PRIVATE Threads::Threads)
