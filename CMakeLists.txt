cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 17)
project("PorFavorCompila")

add_subdirectory("thirdParty/box2d")

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/resources")
include_directories(${SDL2PP_INCLUDE_DIRS})

add_executable("ui" main.cpp screen.cpp)

target_compile_options("ui" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -pedantic-errors -ggdb -DDEBUG -fno-inline>)
target_link_libraries("ui" PUBLIC SDL2pp::SDL2pp)

include_directories(${SDL2PP_INCLUDE_DIRS})

file(GLOB SHAREDGAME "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.h" )
add_library(SharedGameLib ${SHAREDGAME})

file(GLOB SHARED "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.h" )
add_library(SharedLib ${SHARED})
target_link_libraries(SharedLib PUBLIC SharedGameLib)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.h")
file(GLOB CLIENT "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.cpp")
add_executable(client ${CLIENT} ${HEADER_FILES})

file(GLOB SERVER "${CMAKE_CURRENT_SOURCE_DIR}/server_src/*.cpp")
add_executable(server ${SERVER})

target_compile_options(server PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)
target_link_libraries(server PUBLIC box2d)
target_link_libraries(server PUBLIC SDL2pp::SDL2pp)
target_link_libraries(server PUBLIC SharedLib)
target_link_libraries(server PUBLIC SharedGameLib)

target_compile_options(client PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)
target_link_libraries(client PUBLIC box2d)
target_link_libraries(client PUBLIC SDL2pp::SDL2pp)
target_link_libraries(client PUBLIC SharedLib)
target_link_libraries(client PUBLIC SharedGameLib)

