#pragma once

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

namespace client {

class SocketManager {
public:
  SocketManager(const std::string &addr, const int port)
      : address(addr), port(port), socketFD(-1) {}
  ~SocketManager() { closeServer(); }

  bool connectServer();
  void sendServer(const std::string &data);
  void reconnectServer();
  void closeServer();

private:
  std::string address;
  int port;
  int socketFD;
};
}; // namespace client