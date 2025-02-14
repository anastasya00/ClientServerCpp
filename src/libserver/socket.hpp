#pragma once

#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>

#include <../src/libhandler/handler.hpp>

namespace server {

class SocketManager {
public:
  SocketManager(const std::string &addr, const int port)
      : address(addr), port(port), socketFD(-1), clientSocket(-1) {}
  ~SocketManager() { closeClient(); }

  bool connectClient();
  void receivedClient();
  void waitData();
  void reconnectClient();
  void closeClient();

private:
  handler::HandlerString handler_;
  std::string address;
  int port;
  int socketFD;
  int clientSocket;
  std::string receivedData;
};
}; // namespace server