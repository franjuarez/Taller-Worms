cmake_minimum_required(VERSION "3.16.3")

add_subdirectory("third_party/box2d")

project("main")
set(CMAKE_CXX_STANDARD 17)

file(GLOB ENTITY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/entities/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/entities/*.h")
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

add_executable("main" ${SOURCES} ${ENTITY_SOURCES})

target_compile_options("main" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -ggdb -DDEBUG -fno-inline -Wextra -pedantic -pedantic-errors>)
target_link_libraries("main" PUBLIC box2d)