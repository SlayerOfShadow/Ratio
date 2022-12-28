cmake_minimum_required(VERSION 3.13)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(myUnitTests src/sample_test.cpp)
target_link_libraries(myUnitTests PUBLIC Rational GTest::GTest GTest::Main)
target_compile_features(myUnitTests PRIVATE cxx_std_17)

gtest_discover_tests(myUnitTests)


