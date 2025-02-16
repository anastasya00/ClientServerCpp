#include <csignal>
#include <iostream>
#include <thread>

#include <libclient/libthreads/threads.hpp>

int main() {
  threads::ThreadsManager threadsHandler("127.0.0.1", 5000);

  threadsHandler.startThreads();
  threadsHandler.waitStopThreads();

  return 0;
}
