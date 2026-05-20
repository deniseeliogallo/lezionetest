cmake_minimum_required(VERSION 3.20)
project(esercitazione10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

find_package(Eigen3 CONFIG REQUIRED)
list(APPEND libraries_list PUBLIC Eigen3::Eigen)

add_executable(main_program main.cpp)
target_link_libraries(main_program PRIVATE Eigen3::Eigen)

enable_testing()

add_executable(test_gradiente_coniugato test_grad.cpp)
target_link_libraries(test_gradiente_coniugato PRIVATE Eigen3::Eigen)
add_test(NAME TestGradienteConiugato COMMAND test_gradiente_coniugato)