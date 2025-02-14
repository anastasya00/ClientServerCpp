set(CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(handlerClient SHARED
  libhandler/handler.cpp
  libhandler/handler.hpp)
target_include_directories(handlerClient PRIVATE ${cmake_current_source_dir})

add_library(socketServer SHARED
  libserver/socket.cpp
  libserver/socket.hpp)
target_include_directories(socketServer PRIVATE ${cmake_current_source_dir})

add_subdirectory(libclient)

add_executable(mainClient ${CMAKE_CURRENT_SOURCE_DIR}/../src/client/main.cpp)
target_include_directories(mainClient PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mainClient threadsClient)
target_link_libraries(threadsClient bufferClient handlerClient socketClient)
target_link_libraries(handlerClient bufferClient)

add_executable(mainServer ${CMAKE_CURRENT_SOURCE_DIR}/../src/server/main.cpp)
target_include_directories(mainServer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mainServer socketServer)
target_link_libraries(socketServer handlerClient)


