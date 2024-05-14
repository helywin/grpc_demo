add_executable(greeter_server
        client_server/greeter_server.cpp
)
target_link_libraries(greeter_server proto)


add_executable(greeter_client
        client_server/greeter_client.cpp
)
target_link_libraries(greeter_client proto)

add_executable(publisher
        subscribe_publish/publisher.cpp
)
target_link_libraries(publisher proto)


add_executable(subscriber
        subscribe_publish/subscriber.cpp
)
target_link_libraries(subscriber proto)