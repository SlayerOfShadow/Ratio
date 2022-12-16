cmake_minimum_required(VERSION 3.13)

# give a name to the project
project(Examples)

# find Rationnal
# if build as standalone project, find the lib by yourself ...
# if build transitively 

# collect all cpp files (sometimes considered as bad practice)
file(GLOB_RECURSE src_files_list src/*.cpp)

# for each sample file, make an exe
foreach(src_file ${src_files_list})

    get_filename_component(file_exe ${src_file} NAME_WE)    # define te name of the app (filename Without Extension)
    add_executable(${file_exe} ${src_file})                 # file to compile and name of the app
    target_link_libraries(${file_exe} PRIVATE Rationnal)      # lib dependency
    target_compile_features(${file_exe} PRIVATE cxx_std_11) # use at least c++ 11
    target_compile_options(${file_exe} PRIVATE -Wall -O2)   # specify some compilation flags

    message(STATUS "src file  " ${src_file})
    message(STATUS "exe file  " ${file_exe})

endforeach()







 