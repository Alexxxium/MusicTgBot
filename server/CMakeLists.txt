cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

project(Server)

set(SOURCES
	main.cpp 
	source/TaskQueue.cpp 
	source/ServerQueues.cpp 
)

add_executable(Server ${SOURCES})

target_include_directories(Server PRIVATE include)