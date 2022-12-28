cmake_minimum_required(VERSION 3.13)

# give a name to the project
project(RationalTestProject)

#add myLib
message(STATUS "myLib cmake part ...")
add_subdirectory(myLib INTERFACE)
include_directories(${CMAKE_SOURCE_DIR}/myLib/include) # important : other projects called by this cmake will know this include directory

#add myCode
message(STATUS "myCode cmake part ...")
add_subdirectory(myCode)

# add myTest
find_package(GTest OPTIONAL_COMPONENTS)
if(GTEST_FOUND)
	message(STATUS "myTest cmake part ..." )
	add_subdirectory(myTest)
elseif()
	message(WARNING "google test not found, skipping myTest ..." )
endif()