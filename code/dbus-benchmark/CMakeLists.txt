cmake_minimum_required(VERSION 3.22)
project(dbus-benchmark)

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(dbus SHARED IMPORTED)
set_target_properties(dbus PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../../external/lib/libdbus-1.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../../external/include"
)

add_executable(dbus-benchmark-client
               dbus-client.cc)

target_include_directories(dbus-benchmark-client
    PUBLIC include
    PRIVATE ../../external/include)

find_library(DBUS_LIBRARY dbus-1 HINTS ${CMAKE_SOURCE_DIR}/../../external/lib)

target_link_libraries(dbus-benchmark-client
                      rt
                      pthread
                      dl
                      ${DBUS_LIBRARY})


add_executable(dbus-benchmark-server
               dbus-server.cc)

target_include_directories(dbus-benchmark-server
    PUBLIC include
    PRIVATE ../../external/include)

target_link_libraries(dbus-benchmark-server
                      rt
                      pthread
                      dl
                      ${DBUS_LIBRARY})
