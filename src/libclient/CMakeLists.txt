add_library(bufferClient SHARED
  libbuffer/buffer.cpp
  libbuffer/buffer.hpp)
target_include_directories(bufferClient PRIVATE ${cmake_current_source_dir})

add_library(socketClient SHARED
  libsocket/socket.cpp
  libsocket/socket.hpp)
target_include_directories(socketClient PRIVATE ${cmake_current_source_dir})

add_library(threadsClient SHARED
  libthreads/threads.cpp
  libthreads/threads.hpp)
target_include_directories(threadsClient PRIVATE ${cmake_current_source_dir})