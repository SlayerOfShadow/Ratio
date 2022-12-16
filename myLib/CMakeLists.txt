cmake_minimum_required(VERSION 3.13)

# give a name to the project
project(Rationnal)

# automatic get all files in a directory
file(GLOB_RECURSE source_files src/*.cpp)
file(GLOB_RECURSE header_files include/*.hpp)

# call the CMakeLists.txt to make the documentation (Doxygen)
find_package(Doxygen OPTIONAL_COMPONENTS QUIET)
if(DOXYGEN_FOUND)
	add_subdirectory(doc)
else()
	message(WARNING "Doxygen not found, skip dococumentation")
endif()

# Instructions to compile a library (no main() inside)
# default STATIC ??
# SHARED to make a .so instead of a .a
# add_library(ganQ SHARED ${source_files} ${header_files})
add_library(Rationnal ${source_files} ${header_files})

# compilation flags
target_compile_features(Rationnal PRIVATE cxx_std_11) # use at least c++ 11
target_compile_options(Rationnal PRIVATE -Wall -O2)   # specify some compilation flags

# include directory
target_include_directories(Rationnal PUBLIC "include")

# install (optional, install a lib is not mandatory)
install(FILES ${header_files} DESTINATION /usr/local/include/Rationnal)
install(TARGETS Rationnal
        RUNTIME DESTINATION /usr/local/lib
        LIBRARY DESTINATION /usr/local/lib
        ARCHIVE DESTINATION /usr/local/lib)

