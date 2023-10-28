cmake_minimum_required(VERSION "3.16.3")

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

project("quieroquecompile")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/resources")
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable("ui" main.cpp screen.cpp)

target_compile_options("ui" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -pedantic-errors>)
target_link_libraries("ui" PUBLIC SDL2pp::SDL2pp)