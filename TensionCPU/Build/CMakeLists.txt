cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project (TensionCPU)
include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger/Build)
set (SOURCE_FILES_DIR "../Source")
add_executable(TensionCPU.x86 

${SOURCE_FILES_DIR}/main.cpp

#interfaces

${SOURCE_FILES_DIR}/ITension-Cpu.h
${SOURCE_FILES_DIR}/ICmd-Args-Parser.h
${SOURCE_FILES_DIR}/ICpu-Load-Generator.h
${SOURCE_FILES_DIR}/ITimer.h

#headers
${SOURCE_FILES_DIR}/Tension-Cpu.h
${SOURCE_FILES_DIR}/Cmd-Arguments.h
${SOURCE_FILES_DIR}/Cmd-Args-Parser.h
${SOURCE_FILES_DIR}/Cmd-Arguments.h
${SOURCE_FILES_DIR}/Timer.h
${SOURCE_FILES_DIR}/Scheduling-Policy-Type.h

#source
${SOURCE_FILES_DIR}/Tension-Cpu.cpp
${SOURCE_FILES_DIR}/Cmd-Arguments.cpp
${SOURCE_FILES_DIR}/Cmd-Args-Parser.cpp
${SOURCE_FILES_DIR}/Cmd-Arguments.h
${SOURCE_FILES_DIR}/Timer.cpp

)

target_link_libraries(TensionCPU.x86 libEquinoxLogger.a)
target_link_libraries(TensionCPU.x86 pthread)