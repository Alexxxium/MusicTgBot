set(SERVER
	main.cpp 
	source/TaskQueue.cpp 
	source/ServerQueues.cpp 
	"source/ServerConstants.cpp" 
	source/ServerOperations.cpp 
	include/TaskQueue.h 
	include/ServerQueues.h 
	"include/ServerConstants.h" 
	include/ServerOperations.h 
)

add_executable(Server ${SERVER})

target_include_directories(Server PRIVATE
    include 
)

target_link_libraries(Server ${TgBot} ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES})
