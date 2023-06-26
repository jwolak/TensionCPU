# TensionCPU 2.0 Unit tests
# Author: Janusz Wolak
# Copyrights (C) 2023

#------------------------------------------------------------------------------------------
#                                CMAKE settings
#------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22.1)

#------------------------------------------------------------------------------------------
#                                Project dependencies
#------------------------------------------------------------------------------------------
message(STATUS "Searching GTest...")
find_package(GTest REQUIRED)

#------------------------------------------------------------------------------------------
#                                Project settings
#------------------------------------------------------------------------------------------
set(PROJECT_NAME TensionCpuTests.x86)
project(${PROJECT_NAME})

message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${LIB_VERSION_STRING})
message(STATUS "CMAKE_SOURCE_DIR:	" ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#------------------------------------------------------------------------------------------
#                                Tested project includes
#------------------------------------------------------------------------------------------
set(TENSION_CPU_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/../include)

#------------------------------------------------------------------------------------------
#                                Tested project source
#------------------------------------------------------------------------------------------
set(TENSION_CPU_SRC_DIR ${PROJECT_SOURCE_DIR}/../src)

set(TENSION_CPU_SRC 
	${TENSION_CPU_SRC_DIR}/CmdArgumentsParser/ParsedCmdArgumentsLogic.cpp
)

#------------------------------------------------------------------------------------------
#                                Tests source
#------------------------------------------------------------------------------------------
set(TENSION_CPU_TESTS_DIR
	${PROJECT_SOURCE_DIR}/src
)

set(TENSION_CPU_TESTS_SRC
	${TENSION_CPU_TESTS_DIR}/ParsedCmdArgumentsLogicTest.cpp
)

#------------------------------------------------------------------------------------------
#                                Mocks includes
#------------------------------------------------------------------------------------------
set(TENSION_CPU_MOCKS_INCLUDE_DIR
	${PROJECT_SOURCE_DIR}/Mocks
)

include_directories(${TENSION_CPU_INCLUDE_DIR} ${TENSION_CPU_MOCKS_INCLUDE_DIR})

#------------------------------------------------------------------------------------------
#                                Tests target
#------------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME} ${TENSION_CPU_SRC} ${TENSION_CPU_TESTS_SRC})

#------------------------------------------------------------------------------------------
#                                Tests target links
#------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} gmock gtest gtest_main pthread)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} gtest_main)