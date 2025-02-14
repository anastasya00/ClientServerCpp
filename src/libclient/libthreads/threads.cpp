#include <libclient/libthreads/threads.hpp>

void threads::ThreadsManager::startThreads() {
  std::lock_guard<std::mutex> lock(threadMutex);
  stopFlag = false;

  inputThread = std::thread(&ThreadsManager::inputHandler, this);
  processingThread = std::thread(&ThreadsManager::processingHandler, this);
}

void threads::ThreadsManager::stopThreads() {
  {
    std::lock_guard<std::mutex> lock(threadMutex);
    stopFlag = true;
  }
  threadCV.notify_all();

  if (inputThread.joinable())
    inputThread.join();
  if (processingThread.joinable())
    processingThread.join();
}

void threads::ThreadsManager::waitStopThreads() {
  if (inputThread.joinable())
    inputThread.join();
  if (processingThread.joinable())
    processingThread.join();
}

void threads::ThreadsManager::inputHandler() {
  try {
    while (true) {
      std::string inputStr;

      {
        std::lock_guard<std::mutex> lock(threadMutex);
        std::cout << "\nВведите строку (цифры, до 64 элементов): ";
      }
      std::getline(std::cin, inputStr);
      std::this_thread::sleep_for(std::chrono::milliseconds(50));

      if (!std::all_of(inputStr.begin(), inputStr.end(), ::isdigit) &&
          inputStr.length() > 64 && inputStr.empty()) {
        std::cout << "Длина строки должна не превышать 64 символа и состоять "
                     "только из цифр."
                  << std::endl;
        continue;
        ;
      }
      handler_.sortAndReplace(inputStr);

      {
        std::lock_guard<std::mutex> lock(threadMutex);
        buffer_.setData(inputStr);
      }
      threadCV.notify_all();
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  } catch (const std::exception &ex) {
    std::cerr << "Ошибка потока обработки входной строки." << std::endl;
  }
}

void threads::ThreadsManager::processingHandler() {
  try {
    client::SocketManager socket_("127.0.0.1", 5000);

    while (true) {
      std::string bufferData;
      {
        std::unique_lock<std::mutex> lock(threadMutex);
        threadCV.wait(lock,
                      [this]() { return buffer_.getReady() || stopFlag; });
        if (stopFlag)
          break;

        bufferData = buffer_.getData();
        buffer_.clearData();
      }

      int sumElemBuff = handler_.calcSumElem(bufferData);
      {
        std::lock_guard<std::mutex> lock(threadMutex);
        std::cout << "Сумма элементов строки: " << sumElemBuff << std::endl;
      }

      if (socket_.connectServer()) {
        socket_.sendServer(std::to_string(sumElemBuff));

      } else {
        {
          std::lock_guard<std::mutex> lock(threadMutex);
          socket_.reconnectServer();
        }
        continue;
      }
    }
  } catch (const std::exception &ex) {
    std::cerr << "Ошибка потока обработки данных буфера." << std::endl;
  }
}
