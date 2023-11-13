cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 17)
project("Worms")

set(CMAKE_PREFIX_PATH "~/Qt/5.15.15/gcc_64")


set(TESTING OFF CACHE BOOL "Enable testing mode")

if(TESTING)
    add_definitions(-DTESTING)
    endif()
    
    add_subdirectory("thirdParty/box2d")
    
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    
    
    set(SDL2PP_WITH_IMAGE ON)
    set(SDL2PP_WITH_MIXER ON)
    set(SDL2PP_WITH_TTF ON)
    add_subdirectory("thirdParty/SDL2pp")
    
    
    include_directories(${SDL2PP_INCLUDE_DIRS})
    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    
    file(GLOB UI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ui_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/ui_src/*.h")
    
    add_library(SharedUi ${UI})
    target_link_libraries(SharedUi PUBLIC SDL2pp::SDL2pp)
    
    file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.h")
    
    add_library(SharedPhysics ${SOURCES})
    target_link_libraries(SharedPhysics PUBLIC box2d)
    
    file(GLOB SHAREDGAME CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.h" )
    add_library(SharedGameLib ${SHAREDGAME})
    target_link_libraries(SharedGameLib PUBLIC SharedPhysics)
    target_link_libraries(SharedUi PUBLIC SharedGameLib)
    
    file(GLOB SHARED CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.h" )
    add_library(SharedLib ${SHARED})
    target_link_libraries(SharedLib PUBLIC SharedGameLib)
    
    #QT
    set(CMAKE_PREFIX_PATH ~/Qt/5.15.2/gcc_64/)

    find_package(Qt5Widgets CONFIG REQUIRED)
    # find_package(Qt5Core CONFIG REQUIRED)
    include_directories(${PROJECT_SOURCE_DIR}/Lobby  ${Qt5Widgets_INCLUDE_DIRS})
    qt5_wrap_ui(UI_HEADERS 
                            ./Lobby/connectwindow.ui
                            ./Lobby/joinscreen.ui
                            ./Lobby/main_lobby_window.ui)


    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)

    include_directories(${PROJECT_BINARY_DIR})

    file(GLOB LOBBY CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Lobby/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/Lobby/*.h")
    add_library(Lobby ${LOBBY} ${UI_HEADERS})
    set_target_properties(Lobby PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
    target_link_libraries(Lobby PUBLIC SharedUi)
    
    file(GLOB MAIN CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    file(GLOB HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.h")
    file(GLOB CLIENT CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.cpp")
add_executable(client ${MAIN} ${CLIENT} ${HEADER_FILES})

file(GLOB SERVER CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/server_src/*.cpp")
add_library(serverLibrary ${SERVER})

target_link_libraries(serverLibrary PRIVATE Threads::Threads)
target_link_libraries(serverLibrary PUBLIC SharedLib)
target_link_libraries(serverLibrary PUBLIC SharedGameLib)

add_executable(server ${SERVER})

target_compile_options(server PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)
target_link_libraries(server PRIVATE Threads::Threads)
target_link_libraries(server PUBLIC SharedLib)
target_link_libraries(server PUBLIC SharedGameLib)

target_link_libraries(Lobby PUBLIC serverLibrary)

target_compile_options(client PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)
target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(client PUBLIC SharedLib)
target_link_libraries(client PUBLIC SharedGameLib)
target_link_libraries(client PUBLIC SharedUi)
target_link_libraries(client PUBLIC Lobby)
target_link_libraries(client PUBLIC Qt5::Widgets Qt5::Core)


# add_executable("ui" main.cpp worm.cpp game_view.cpp worm_view.cpp worm.cpp constants.cpp game_view.cpp mouse_handler.cpp)
# 
# target_compile_options("ui" PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>: -ggdb -Wall -Wextra -pedantic -pedantic-errors>)
# target_link_libraries("ui" PUBLIC SDL2pp::SDL2pp)