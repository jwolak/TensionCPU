# TensionCPU 2.0 Unit tests
# Author: Janusz Wolak
# Copyrights (C) 2023

cmake_minimum_required(VERSION 2.8.9)

set(PROJECT_NAME TensionCpuTests.x86)
project(${PROJECT_NAME})

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${LIB_VERSION_STRING})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)

set(TENSION_CPU_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)
set(TENSION_CPU_SRC ${PROJECT_SOURCE_DIR}/../src)


set(TENSION_CPU_TESTS_DIR
	${PROJECT_SOURCE_DIR}/src
)

set(TENSION_CPU_TESTS_SRC
	${TENSION_CPU_TESTS_DIR}/ParsedCmdArgumentsLogicTest.cpp
)

set(TENSION_CPU_MOCKS_INCLUDE_DIR
	${PROJECT_SOURCE_DIR}/Mocks
)

include_directories(${TENSION_CPU_INCLUDE_DIR} ${TENSION_CPU_MOCKS_INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${TENSION_CPU_SRC} ${TENSION_CPU_TESTS_SRC})

target_link_libraries(${PROJECT_NAME} gmock gtest gtest_main pthread)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} gtest_main)