cmake_minimum_required(VERSION "3.16.3")

add_subdirectory("third_party/box2d")

project("main")
set(CMAKE_CXX_STANDARD 17)

add_executable("main" main.cpp game_world.cpp listener.cpp physics_constants.h)

target_compile_options("main" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -ggdb -DDEBUG -fno-inline -Wextra -pedantic -pedantic-errors>)
target_link_libraries("main" PUBLIC box2d)