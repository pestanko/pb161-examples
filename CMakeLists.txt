cmake_minimum_required(VERSION 3.0)
project(vyuka)

if (CMAKE_CXX_COMPILER_ID MATCHES Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  # using regular Clang or AppleClang or GCC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic -Wold-style-cast")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
  # using Visual Studio C++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std=c++17 /W4 /WX")
  add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif()

add_executable(builder builder.cpp)
add_executable(function function.cpp)
add_executable(publish publish.cpp)
add_executable(references references.cpp)
add_executable(unique unique.cpp)

