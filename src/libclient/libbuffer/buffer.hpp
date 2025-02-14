#pragma once

#include <condition_variable>
#include <iostream>
#include <mutex>

namespace buffer {

class Buffer {
public:
  Buffer() : ready(false){};

  std::string getData();
  void setData(const std::string newBuffer);
  void clearData();
  bool getReady();

private:
  std::string data;
  bool ready;
  std::mutex bufferMutex;
  std::condition_variable bufferCV;
};
}; // namespace buffer
