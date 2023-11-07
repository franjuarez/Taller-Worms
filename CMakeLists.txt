cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 17)
project("PorFavorCompila")

add_subdirectory("thirdParty/box2d")

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.h")

add_library(SharedPhysics ${SOURCES})
target_link_libraries(SharedPhysics PUBLIC box2d)

file(GLOB SHAREDGAME "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.h" )
add_library(SharedGameLib ${SHAREDGAME})
target_link_libraries(SharedGameLib PUBLIC SharedPhysics)


file(GLOB SHARED "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.h" )
add_library(SharedLib ${SHARED})
target_link_libraries(SharedLib PUBLIC SharedGameLib)

file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.h")
file(GLOB CLIENT "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.cpp")
add_executable(client ${CLIENT} ${HEADER_FILES})

file(GLOB SERVER "${CMAKE_CURRENT_SOURCE_DIR}/server_src/*.cpp")
add_executable(server ${SERVER})

target_compile_options(server PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)
target_link_libraries(server PUBLIC SharedLib)
target_link_libraries(server PUBLIC SharedGameLib)

target_compile_options(client PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)
target_link_libraries(client PUBLIC SharedLib)
target_link_libraries(client PUBLIC SharedGameLib)




# add_subdirectory("third_party/box2d")

# file(GLOB ENTITY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/entities/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/entities/*.h")
# file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.h")

# add_executable("main" ${SOURCES} ${ENTITY_SOURCES})

# target_compile_options("main" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -ggdb -DDEBUG -fno-inline -Wextra -pedantic -pedantic-errors>)
# target_link_libraries("main" PUBLIC box2d)