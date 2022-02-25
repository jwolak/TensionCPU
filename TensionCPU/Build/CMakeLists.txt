cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project (TensionCPU)
include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger/Build)
set (SOURCE_FILES_DIR "../Source")
add_executable(TensionCPU.x86 

${SOURCE_FILES_DIR}/main.cpp

#interfaces

#headers

#source

)

target_link_libraries(TensionCPU.x86 libEquinoxLogger.a)