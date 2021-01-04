cmake_minimum_required(VERSION 3.0)
project(httpserver)

message("===http server===\n")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIRSRCS)

add_executable(httpserver ${DIRSRCS} httpserver_test.cc)
add_executable(httpclient ${DIRSRCS} client.cc)



