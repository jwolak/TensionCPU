cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project (TensionCPU)
add_executable(TensionCPU.x86 

../Source/main.cpp 

#interfaces
../Source/Logger/ILogger.h
../Source/Logger/ILogs-File-Access-Guard.h
../Source/Logger/IFile-Logger.h
../Source/Logger/IConsole-Logger.h
../Source/Logger/ILogger-Level.h

#headers
../Source/Logger/Logger.h
../Source/Logger/Log-Level-Type.h
../Source/Logger/Log-Output-Type.h
../Source/Logger/Logs-File-Access-Guard.h
../Source/Logger/File-Logger.h
../Source/Logger/Console-Logger.h
../Source/Logger/Logger-Level.h

#source
../Source/Logger/Logger.cpp
../Source/Logger/Logs-File-Access-Guard.cpp
../Source/Logger/File-Logger.cpp
../Source/Logger/Console-Logger.cpp
../Source/Logger/Logger-Level.cpp
)
