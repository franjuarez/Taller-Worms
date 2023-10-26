cmake_minimum_required(VERSION "3.16.3")

add_subdirectory("thirdParty/box2d")

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

project("PorFavorCompila")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable("PorFavorCompila" main.cpp screen.cpp motor.cpp)

target_compile_options("PorFavorCompila" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -pedantic-errors>)
target_link_libraries("PorFavorCompila" PUBLIC box2d)
target_link_libraries("PorFavorCompila" PUBLIC SDL2pp::SDL2pp)