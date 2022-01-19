cmake_minimum_required(VERSION 3.22)
project(dbus2-test)

# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(dbus SHARED IMPORTED)
set_target_properties(dbus PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../../external/lib/libdbus-1.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../../external/include"
)

add_executable(dbus-test2
               dbus-test2.cpp)

target_include_directories(dbus-test2
    PUBLIC include
    PRIVATE ../../external/include)

find_library(DBUS_LIBRARY dbus-1 HINTS ${CMAKE_SOURCE_DIR}/../../external/lib)

target_link_libraries(dbus-test2
                      rt
                      pthread
                      dl
                      ${DBUS_LIBRARY})
