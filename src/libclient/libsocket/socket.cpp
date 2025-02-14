#include <libclient/libsocket/socket.hpp>

bool client::SocketManager::connectServer() {
  if (socketFD != -1) {
    closeServer();
  }

  socketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFD == -1) {
    std::cerr << "Ошибка при создании сокета." << std::endl;
    return false;
  }

  sockaddr_in addrServer{};
  addrServer.sin_family = AF_INET;
  addrServer.sin_port = htons(port);

  if (inet_pton(AF_INET, address.c_str(), &addrServer.sin_addr) <= 0) {
    std::cerr << "Ошибка при преобразовании адреса сервера в формат для сети."
              << std::endl;
    closeServer();
    return false;
  }

  if (connect(socketFD, (struct sockaddr *)&addrServer, sizeof(addrServer)) <
      0) {
    std::cerr << "Ошибка при подключении к серверу." << std::endl;
    closeServer();
    return false;
  }

  std::cout << "Подключение к серверу установлено." << std::endl;
  return true;
}

void client::SocketManager::sendServer(const std::string &data) {
  if (send(socketFD, data.c_str(), data.size(), 0) < 0) {
    std::cerr << "Ошибка при отправке данных на сервер." << std::endl;
    return;
  }
  std::cout << "Данные отправлены." << std::endl;
}

void client::SocketManager::reconnectServer() {
  for (int i = 0; i < 3; i++) {
    std::cout << "Попытка переподключения к серверу №" << i + 1 << std::endl;
    if (connectServer()) {
      return;
    }
    sleep(2);
  }
}

void client::SocketManager::closeServer() {
  if (socketFD != -1) {
    close(socketFD);
    socketFD = -1;
  }
}