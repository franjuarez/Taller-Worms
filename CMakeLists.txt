cmake_minimum_required(VERSION "3.16.3")

set(CMAKE_CXX_STANDARD 17)
project("Worms")

#poner o sacar esta linea dependiendo de si estas en la compu de joaco o en una con qt-dev actualizado
set(CMAKE_PREFIX_PATH "~/Qt/5.15.15/gcc_64")

#Agregando Catch2
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/Catch2")
include(CTest)
include(Catch)

#Dependencias comunes
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#Agregando Box2d
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/box2d")

#Agregando Yaml-cpp
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/yaml-cpp-0.8.0")

#Agregando SDL2pp
set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory("thirdParty/SDL2pp")

include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#SHARED
file(GLOB SHARED CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/shared_src/*.h" )
add_library(SharedLib ${SHARED})
target_link_libraries(SharedLib PUBLIC yaml-cpp)

#UI
file(GLOB UI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/ui_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/ui_src/*.h")
add_library(SharedUi ${UI})
target_link_libraries(SharedUi PUBLIC SDL2pp::SDL2pp)

#PHYSICS
file(GLOB HANDLERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/query_handlers/*.cpp")
file(GLOB ENTITIES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/entities/*.cpp")
file(GLOB PROJECTILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/entities/projectiles/*.cpp")
file(GLOB SUPPLY_BOX CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/entities/supplies/*.cpp")
file(GLOB AUX CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/aux/*.cpp")
file(GLOB SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/physics_src/*.cpp")
add_library(SharedPhysics ${SOURCES} ${ENTITIES} ${PROJECTILES} ${SUPPLY_BOX} ${HANDLERS} ${AUX})
target_link_libraries(SharedPhysics PUBLIC box2d SharedLib)

#GAME
file(GLOB SHAREDGAME CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/commands/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/commands/*.h" )
file(GLOB COMMANDS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/game_src/commands/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/commands/*.h" )
file(GLOB MAPS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/game_src/map_loading/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/game_src/map_loading/*.h" )
add_library(SharedGameLib ${SHAREDGAME} ${COMMANDS} ${MAPS})
target_link_libraries(SharedGameLib PUBLIC SharedPhysics)
target_link_libraries(SharedGameLib PUBLIC yaml-cpp)
target_link_libraries(SharedLib PUBLIC SharedGameLib)
target_link_libraries(SharedUi PUBLIC SharedGameLib)

#QT
find_package(Qt5Widgets CONFIG REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/client_gui  ${Qt5Widgets_INCLUDE_DIRS})
qt5_wrap_ui(UI_HEADERS 
                        ./client_gui/chooseoptionwindow.ui
                        ./client_gui/choosingwindow.ui
                        ./client_gui/connectionwindow.ui
                        ./client_gui/createwindow.ui
                        ./client_gui/joinwindow.ui)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${PROJECT_BINARY_DIR})

#CLIENT GUI
file(GLOB CLIENT_GUI CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_gui/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/client_gui/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/client_gui/*.qrc")
add_library(client_gui ${CLIENT_GUI} ${UI_HEADERS})
set_target_properties(client_gui PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
target_link_libraries(client_gui PUBLIC SharedUi)

#EXECUTABLE CLIENT
file(GLOB MAIN CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_gui/main.cpp")
file(GLOB HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.h")
file(GLOB CLIENT CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.cpp")
list(REMOVE_ITEM CLIENT "${CMAKE_CURRENT_SOURCE_DIR}/client_src/client_main.cpp")
add_executable(wormsClient ${MAIN} ${CLIENT} ${HEADER_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/client_gui/resources.qrc)

# SERVER
file(GLOB SERVER CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/server_src/*.cpp")
add_library(serverLibrary ${SERVER})

target_link_libraries(serverLibrary PRIVATE Threads::Threads)
target_link_libraries(serverLibrary PUBLIC SharedLib)
target_link_libraries(serverLibrary PUBLIC SharedGameLib)

add_executable(wormsServer ${SERVER})

target_link_libraries(wormsServer PRIVATE Threads::Threads)
target_link_libraries(wormsServer PUBLIC SharedLib)
target_link_libraries(wormsServer PUBLIC SharedGameLib)
target_link_libraries(wormsServer PRIVATE yaml-cpp)
target_compile_options(wormsServer PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)

target_link_libraries(client_gui PUBLIC serverLibrary)
target_link_libraries(wormsClient PRIVATE Threads::Threads)
target_link_libraries(wormsClient PUBLIC SharedLib)
target_link_libraries(wormsClient PUBLIC SharedGameLib)
target_link_libraries(wormsClient PUBLIC SharedUi)
target_link_libraries(wormsClient PUBLIC client_gui)
target_link_libraries(wormsClient PUBLIC Qt5::Widgets Qt5::Core)
target_link_libraries(wormsClient PRIVATE yaml-cpp)
target_compile_options(wormsClient PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)

#CLIENT SOURCE
file(GLOB CLIENT_2 CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client_src/*.cpp")
add_executable(client ${CLIENT_2} ${HEADER_FILES})
target_link_libraries(client PRIVATE Threads::Threads)
target_link_libraries(client PUBLIC SharedLib)
target_link_libraries(client PUBLIC SharedGameLib)
target_link_libraries(client PUBLIC SharedUi)
target_link_libraries(client PRIVATE yaml-cpp)
target_compile_options(client PRIVATE $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic -ggdb -DDEBUG -pedantic-errors>)


#TESTS
# file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
# add_executable(tests ${TEST_SOURCES})
# target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
# target_link_libraries(tests PUBLIC SharedLib)
# target_link_libraries(tests PUBLIC SharedGameLib)

# catch_discover_tests(tests)

#Installer

set(BIN_INSTALL_DIR "/usr/bin")
set(SHARED_DIR "/usr/lib/TPworms")
set(CONF_INSTALL_DIR "/etc/TPworms")
set(VAR_INSTALL_DIR "/var/TPworms")

install(TARGETS wormsClient wormsServer DESTINATION ${BIN_INSTALL_DIR}  PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install(TARGETS SharedLib SharedUi SharedPhysics SharedGameLib client_gui serverLibrary DESTINATION ${SHARED_DIR} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/maps" "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION ${VAR_INSTALL_DIR} FILE_PERMISSIONS WORLD_READ WORLD_WRITE)
install(FILES "configuration.yaml" DESTINATION ${CONF_INSTALL_DIR} PERMISSIONS WORLD_READ WORLD_WRITE)

