#include <csignal>
#include <iostream>
#include <thread>

#include <libclient/libthreads/threads.hpp>

int main() {
  threads::ThreadsManager threadsHandler;

  threadsHandler.startThreads();
  threadsHandler.waitStopThreads();

  return 0;
}
