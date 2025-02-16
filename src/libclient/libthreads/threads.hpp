#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include <../src/libhandler/handler.hpp>
#include <libclient/libbuffer/buffer.hpp>
#include <libclient/libsocket/socket.hpp>

namespace threads {

class ThreadsManager {
public:
  ThreadsManager(const std::string &addr, const int port)
      : address(addr), port(port), stopFlag(false){};
  ~ThreadsManager() { stopThreads(); }

  void startThreads();
  void stopThreads();
  void waitStopThreads();
  void inputHandler();
  void processingHandler();

private:
  buffer::Buffer buffer_;
  handler::HandlerString handler_;
  std::thread inputThread;
  std::thread processingThread;
  std::mutex threadMutex;
  std::condition_variable threadCV;
  bool stopFlag;
  std::string address;
  int port;
};
}; // namespace threads