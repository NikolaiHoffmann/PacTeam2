cmake_minimum_required(VERSION 3.13)
project(PacTeam2)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
add_compile_options(-Wall -Wextra)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)