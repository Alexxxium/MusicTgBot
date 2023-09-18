set(SERVER
	main.cpp 
	source/ServerQueues.cpp 
	source/ServerConstants.cpp 
	source/ServerOperations.cpp 
	source/ServerData.cpp 
	source/Server.cpp 
	patterns/source/TaskQueue.cpp 
    patterns/source/TaskQueueWrapp.cpp 
)

add_executable(Server ${SERVER})

target_include_directories(Server PRIVATE
    include 
	patterns/include 
)

target_link_libraries(Server ${TgBot} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
