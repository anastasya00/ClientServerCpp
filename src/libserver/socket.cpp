#include <libserver/socket.hpp>

bool server::SocketManager::connectClient() {
  if (socketFD != -1) {
    closeClient();
  }

  socketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFD == -1) {
    std::cerr << "Ошибка при создании сокета." << std::endl;
    return false;
  }

  sockaddr_in addrClient{};
  addrClient.sin_family = AF_INET;
  addrClient.sin_port = htons(port);

  if (inet_pton(AF_INET, address.c_str(), &addrClient.sin_addr) <= 0) {
    std::cerr << "Ошибка при преобразовании адреса клиента в формат для сети."
              << std::endl;
    closeClient();
    return false;
  }

  if (bind(socketFD, (struct sockaddr *)&addrClient, sizeof(addrClient)) ||
      listen(socketFD, 5) < 0) {
    std::cerr << "Ошибка при подключении к клиенту." << std::endl;
    closeClient();
    return false;
  }
  return true;
}

void server::SocketManager::receivedClient() {
  if (handler_.checkStringLength(receivedData)) {
    std::cout << "Полученные данные от клиента: " << receivedData << "\n"
              << std::endl;
  } else {
    std::cout << "Данные не подошли под критерии: строка не менее 2 символов, "
                 "число кратно 32\n"
              << std::endl;
  }
}

void server::SocketManager::waitData() {
  while (true) {
    std::cout << "Ожидание данных от клиента..." << std::endl;

    int clientSocket = accept(socketFD, nullptr, nullptr);
    if (clientSocket == -1) {
      std::cerr << "Ошибка при принятии соединения." << std::endl;
      continue;
    }

    char* buffer = new char[1024];
    ssize_t byteRead = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (byteRead > 0) {
      receivedData = buffer;
      delete[] buffer;
      receivedClient();
    } else {
      std::cerr << "Ошибка при чтении данных от клиента." << std::endl;
      close(clientSocket);
      delete[] buffer;
    }
    close(clientSocket);
  }
}

void server::SocketManager::reconnectClient() {
  while (!connectClient()) {
    std::cerr << "Повторная попытка подключения к клиенту..." << std::endl;
    sleep(2);
  }
}

void server::SocketManager::closeClient() {
  if (socketFD != -1) {
    close(socketFD);
    socketFD = -1;
  }
}