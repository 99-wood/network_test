cmake_minimum_required(VERSION 3.5)
set( CMAKE_CXX_COMPILER "D:/MinGW/bin/g++.exe" )
set( CMAKE_C_COMPILER "D:/MinGW/bin/gcc.exe" )

project (Network)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# include_directories(${PROJECT_SOURCE_DIR}/head)

# add_subdirectory(lib)

# aux_source_directory(./src DIR_SRCS)

add_executable(boardcast_server ./boardcast_server.cpp)
add_executable(boardcast_user ./boardcast_user.cpp)

target_link_libraries(boardcast_server ws2_32)
target_link_libraries(boardcast_server -static-libstdc++ -static-libgcc)
target_link_libraries(boardcast_user ws2_32)
target_link_libraries(boardcast_user -static-libstdc++ -static-libgcc)
# target_link_libraries(Demo sub)