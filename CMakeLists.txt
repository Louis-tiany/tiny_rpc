cmake_minimum_required(VERSION 3.0)
project(httpserver)

message("===http server===\n")

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)
set (PROJECT_LINK_LIBS z)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/protobuf)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIRSRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src/protobuf PROTO_CODEC)

add_executable(httpserver ${DIRSRCS} test/httpserver_test.cc)
add_executable(tcpclient ${DIRSRCS} client.cc)
#add_executable(tcpserver ${DIRSRCS} test.cc)
add_executable(heart_beat ${DIRSRCS} test/heart_beat.cc)



aux_source_directory(${PROJECT_SOURCE_DIR}/test/proto_rpc RPC_SRCS)
#list(REMOVE_ITEM RPC_SRCS ${PROJECT_SOURCE_DIR}/test/proto_rpc/server.cc ${PROJECT_SOURCE_DIR}/test/proto_rpc/client.cc)


aux_source_directory(${PROJECT_SOURCE_DIR}/test/proto_rpc/proto PROTO_SRCS)
include_directories(${PROJECT_SOURCE_DIR}/test/proto_rpc/proto)
add_executable(rpc_server ${DIRSRCS} ${PROTO_CODEC} ${PROTO_SRCS} ${PROJECT_SOURCE_DIR}/test/proto_rpc/server.cc)
target_link_libraries(rpc_server ${PROTOBUF_LIBRARIES} ${PROJECT_LINK_LIBS})

add_executable(rpc_client ${DIRSRCS} ${PROTO_CODEC} ${PROTO_SRCS}  ${PROJECT_SOURCE_DIR}/test/proto_rpc/client.cc)
target_link_libraries(rpc_client ${PROTOBUF_LIBRARIES} ${PROJECT_LINK_LIBS})
