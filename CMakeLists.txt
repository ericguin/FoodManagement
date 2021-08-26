cmake_minimum_required(VERSION 3.20)

project(FoodManagement VERSION 0.0.1)

add_executable(FoodManagement main.cc)

add_subdirectory(components/database)

target_link_libraries(FoodManagement)