target_sources(FoodManagement PRIVATE src/units.cc)
target_include_directories(FoodManagement PUBLIC public)

target_sources(FoodManagementTests PRIVATE src/units.cc test/units_test.cc)
target_include_directories(FoodManagementTests PUBLIC public)