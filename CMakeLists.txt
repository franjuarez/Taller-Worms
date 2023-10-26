cmake_minimum_required(VERSION "3.16.3")

add_subdirectory("thirdParty/box2d")

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

project("PorFavorCompila")
set(CMAKE_CXX_STANDARD 17)
include_directories(${SDL2PP_INCLUDE_DIRS})
add_library(SharedLib shared_src/const.cpp)

set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/client_src/client.h)

set(CLIENT ${CMAKE_CURRENT_SOURCE_DIR}/client_src/client_main.cpp 
            ${CMAKE_CURRENT_SOURCE_DIR}/client_src/client.cpp 
)

add_executable(client ${CLIENT} ${HEADER_FILES})

set(SERVER ${CMAKE_CURRENT_SOURCE_DIR}/server_src/main.cpp)

add_executable(server ${SERVER})

target_compile_options(server PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -pedantic-errors>)
target_link_libraries(server PUBLIC box2d)
target_link_libraries(server PUBLIC SDL2pp::SDL2pp)
target_link_libraries(server PUBLIC SharedLib)

target_compile_options(client PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -pedantic-errors>)
target_link_libraries(client PUBLIC box2d)
target_link_libraries(client PUBLIC SDL2pp::SDL2pp)
target_link_libraries(client PUBLIC SharedLib)
