cmake_minimum_required(VERSION 3.20)

project(FoodManagement VERSION 0.0.1)

add_executable(FoodManagement main.cc)
add_executable(FoodManagementTests test.cc)

add_subdirectory(components/database)
add_subdirectory(components/units)

target_include_directories(FoodManagement PUBLIC lib)
target_include_directories(FoodManagementTests PUBLIC lib)
target_link_libraries(FoodManagementTests CppUTest CppUTestExt)