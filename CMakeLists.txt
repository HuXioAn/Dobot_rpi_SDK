#projrct name
project(Demo CXX)
add_compile_options(-std=c++11)

#head file path
include_directories(inc)

#source directory
aux_source_directory(src DIR_SRCS)

link_libraries(-lpthread -lm)

#set environment variable
set(TEST_MATH ${DIR_SRCS})

#add executable file
add_executable(${PROJECT_NAME} ${TEST_MATH})


