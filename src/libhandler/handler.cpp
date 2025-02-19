#include <libhandler/handler.hpp>

void handler::HandlerString::sortAndReplace(std::string &str) {
  try {
    std::sort(str.begin(), str.end(), std::greater<char>());

    std::string newStr;
    for (char elem : str) {
      newStr += (elem - '0') % 2 == 0 ? "КВ" : std::string(1, elem);
    }
    str = std::move(newStr);
  } catch (const std::exception &ex) {
    std::cerr << "Ошибка при обработке строки." << ex.what() << std::endl;
  }
}

int handler::HandlerString::calcSumElem(const std::string &str) {
  try {
    int sumElemBuff = 0;
    for (char ch : str) {
      if (std::isdigit(ch)) {
        sumElemBuff += ch - '0';
      }
    }
    return sumElemBuff;
  } catch (const std::exception &ex) {
    std::cerr << "Ошибка при суммировании элементов строки." << ex.what()
              << std::endl;
  }
  return 0;
}

bool handler::HandlerString::checkStringLength(const std::string &str) {
  if (str.length() >= 2 && std::stoi(str) % 32 == 0)
    return true;
  return false;
}