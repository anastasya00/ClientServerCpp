#pragma once

#include <algorithm>
#include <iostream>

#include <libclient/libbuffer/buffer.hpp>

namespace handler {

class HandlerString {
public:
  HandlerString() {}

  void sortAndReplace(std::string &str);
  int calcSumElem(const std::string &str);
  bool checkStringLength(const std::string &str);

private:
  int sumElemBuff;
};
}; // namespace handler