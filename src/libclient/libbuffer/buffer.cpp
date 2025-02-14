#include <libclient/libbuffer/buffer.hpp>

void buffer::Buffer::setData(const std::string newData) {
  {
    std::lock_guard<std::mutex> lock(bufferMutex);
    data = newData;
    ready = true;
  }
  bufferCV.notify_one();
}

std::string buffer::Buffer::getData() {
  std::unique_lock<std::mutex> lock(bufferMutex);
  bufferCV.wait(lock, [this]() { return ready; });

  std::string result = data;
  return result;
}

void buffer::Buffer::clearData() {
  std::lock_guard<std::mutex> lock(bufferMutex);
  data.clear();
  ready = false;
}

bool buffer::Buffer::getReady() {
  std::lock_guard<std::mutex> lock(bufferMutex);
  return ready;
}