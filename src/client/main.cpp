#include <csignal>
#include <iostream>
#include <thread>

#include <libclient/libthreads/threads.hpp>

threads::ThreadsManager *globalThreadsHandler = nullptr;

void signalHandler(int signum) {
  if (globalThreadsHandler == nullptr) {
    std::cerr << "Обработчик сигнала не инициализирован." << std::endl;
    return;
  }

  std::cout << "\nПрограмма завершает работу (сигнал: " << signum << ")"
            << std::endl;
  globalThreadsHandler->stopThreads();
}

int main() {
  threads::ThreadsManager threadsHandler;
  globalThreadsHandler = &threadsHandler;

  std::signal(SIGHUP, signalHandler);

  std::cout << "Программа запущена. Нажмите Ctrl+C для выхода.\n" << std::endl;

  threadsHandler.startThreads();
  threadsHandler.waitStopThreads();

  return 0;
}
