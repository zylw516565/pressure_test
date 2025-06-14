cmake_minimum_required(VERSION 2.6)

project (PressureTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -O0 -Wno-unused-variable -Wattributes -pthread")

link_directories(
    /usr/lib64/mysql/
)

#Protobuf
set(PROTOBUF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/thirdparty)
set(PROTOBUF_LIBRARY ${PROJECT_SOURCE_DIR}/src/thirdparty/google/protobuf/lib)
message(STATUS "Protobuf_INCLUDE_DIR = ${PROTOBUF_INCLUDE_DIR}")

find_package(Protobuf REQUIRED)
if(PROTOBUF_FOUND)
  message(STATUS "=== Protobuf_LIBRARIES: ${PROTOBUF_LIBRARY}")
  message(STATUS "=== Protobuf_INCLUDE_DIRS: ${PROTOBUF_INCLUDE_DIR}")
  message(STATUS "=== Protobuf_INCLUDE_DIR: ${PROTOBUF_INCLUDE_DIR}")
  include_directories(${PROTOBUF_INCLUDE_DIR})
  include_directories(${PROJECT_SOURCE_DIR}/src/thirdparty)
  link_directories(${PROTOBUF_LIBRARY})  
else()
  MESSAGE( WARNING "Not found Protobuf")
endif()

#OpenSSL
set(OpenSSL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/thirdparty/openssl/include)
set(OpenSSL_LIBRARY ${PROJECT_SOURCE_DIR}/src/thirdparty/openssl/lib/linux)
message(STATUS "OpenSSL_INCLUDE_DIR = ${OpenSSL_INCLUDE_DIR}")

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
  message(STATUS "=== OpenSSL_LIBRARY: ${OpenSSL_LIBRARY}")
  message(STATUS "=== OpenSSL_INCLUDE_DIRS: ${OpenSSL_INCLUDE_DIR}")
  message(STATUS "=== OpenSSL_INCLUDE_DIR: ${OpenSSL_INCLUDE_DIR}")
  include_directories(${OpenSSL_INCLUDE_DIR})
  include_directories(${PROJECT_SOURCE_DIR}/src/thirdparty)
  link_directories(${OpenSSL_LIBRARY})  
else()
  MESSAGE( WARNING "Not found OpenSSL")
endif()

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)

add_subdirectory(src/muduo/base)
add_subdirectory(src/muduo/net)

file(GLOB base_srcs
src/base/*.cpp
)

file(GLOB common_srcs
src/common/*.cpp
)

set(json_srcs
src/thirdparty/jsoncpp1.9.0/json_reader.cpp
src/thirdparty/jsoncpp1.9.0/json_value.cpp
src/thirdparty/jsoncpp1.9.0/json_writer.cpp
)

set(utils_srcs
src/utils/StringUtil.cpp
src/utils/URLEncodeUtil.cpp
src/utils/MD5.cpp
src/utils/DaemonRun.cpp
src/utils/ini.c
src/utils/INIReader.cpp
src/utils/PB2JSONHelper.cpp
)

set(tcu_srcs
src/main.cpp
src/APPPacketHead.cpp
src/DCMMsgHead.cpp
src/zna_protocol_message.pb.cc
src/TCU.cpp
src/TCUCodec.cpp
)

set(Lib_File
  muduo_base
  muduo_net
  protobuf
  crypto
  ssl
)

add_executable(PressureTest ${tcu_srcs} ${utils_srcs} ${json_srcs} ${base_srcs} ${common_srcs})
TARGET_LINK_LIBRARIES(PressureTest ${Lib_File} )
