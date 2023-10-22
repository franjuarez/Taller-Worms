cmake_minimum_required(VERSION "3.16.3")

add_subdirectory("thirdParty/box2d")

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

project("FIUUUMMMM")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable("FIUUUMMMM" main.cpp screen.cpp game.cpp)

target_compile_options("FIUUUMMMM" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -pedantic-errors>)
target_link_libraries("FIUUUMMMM" PUBLIC box2d)
target_link_libraries("FIUUUMMMM" PUBLIC SDL2pp::SDL2pp)
