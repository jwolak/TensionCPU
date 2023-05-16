# TensionCPU 2.0
# Author: Janusz Wolak
# Copyrights (C) 2023

#------------------------------------------------------------------------------------------
#                                CMAKE settings
#------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.22.1)

#------------------------------------------------------------------------------------------
#                                TensionCPU dependencies
#------------------------------------------------------------------------------------------
message(STATUS "Searching EquinoxLogger...")
find_package(EquinoxLogger REQUIRED)

#------------------------------------------------------------------------------------------
#                                TensionCPU settings
#------------------------------------------------------------------------------------------
project(TensionCPU VERSION 2.0.0)
message(STATUS "Processing CMakeLists.txt for: " ${PROJECT_NAME} " " ${VERSION})
message(STATUS "CMAKE_SOURCE_DIR:    " ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++ standard set to: " ${CMAKE_CXX_STANDARD})

#------------------------------------------------------------------------------------------
#                                TensionCPU options
#------------------------------------------------------------------------------------------
option(TENSION_CPU_TESTS        "Build tests"        OFF)
if(TENSION_CPU_TESTS)
    message(STATUS "Build test enabled")
endif()

#------------------------------------------------------------------------------------------
#                                TensionCPU include
#------------------------------------------------------------------------------------------
set(TENSION_CPU_INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

include_directories(${PROJECT_NAME} PRIVATE  ${TENSION_CPU_INCLUDE})

#------------------------------------------------------------------------------------------
#                                TensionCPU source directory
#------------------------------------------------------------------------------------------
set(TENSION_CPU_SRC_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#------------------------------------------------------------------------------------------
#                                TensionCPU source
#------------------------------------------------------------------------------------------
set(TENSION_CPU_SRC
    ${TENSION_CPU_SRC_DIR}/main.cpp
    ${TENSION_CPU_SRC_DIR}/TensionCPU.cpp
    ${TENSION_CPU_SRC_DIR}/CmdArgumentsParser.cpp
    ${TENSION_CPU_SRC_DIR}/ParsedCmdArguments.cpp
)

#------------------------------------------------------------------------------------------
#                                TensionCPU target
#------------------------------------------------------------------------------------------
add_executable(${PROJECT_NAME}.x86 ${TENSION_CPU_SRC})

#------------------------------------------------------------------------------------------
#                                TensionCPU target links
#------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}.x86 EquinoxLogger)

#------------------------------------------------------------------------------------------
#                                TensionCPU tests
#------------------------------------------------------------------------------------------
if(TENSION_CPU_TESTS)
    add_subdirectory(tests)
    message(STATUS "Tests subdirectory added")
endif(TENSION_CPU_TESTS)
