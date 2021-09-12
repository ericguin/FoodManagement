cmake_minimum_required(VERSION 3.20)

project(FoodManagement VERSION 0.0.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui Qml Quick)

add_executable(FoodManagement main.cc qml.qrc)
add_executable(FoodManagementTests test.cc)

add_subdirectory(components/database)
add_subdirectory(components/units)
add_subdirectory(components/ui)

target_include_directories(FoodManagement PUBLIC lib)
target_include_directories(FoodManagementTests PUBLIC lib)

target_link_libraries(FoodManagement PUBLIC Qt5::Widgets Qt5::Qml Qt5::Quick)

target_link_libraries(FoodManagementTests CppUTest CppUTestExt)
