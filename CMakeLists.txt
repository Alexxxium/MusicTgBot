cmake_minimum_required(VERSION 3.8)

project(MusicBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)

include_directories(${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})

if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

set(TgBot "D:/Libs/vcpkg/installed/x64-windows/lib/TgBot.lib")

set(SOURCES
    main.cpp 
    controller/BotController.cpp 
    constants/constants.cpp 
    model/commands/source/AnyCommands.cpp 
    model/commands/source/InlineCommands.cpp 
    model/commands/source/MacroCommands.cpp 
    model/commands/source/Command.cpp 
    model/keyboards/InlKeyboardFactory.cpp 
    core/source/validators.cpp
    core/source/userdata.cpp
)

add_executable(MusicBot ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    constants
    controller
    model/commands/include
    model/keyboards 
    core/include 
)

target_link_libraries(MusicBot ${TgBot} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
