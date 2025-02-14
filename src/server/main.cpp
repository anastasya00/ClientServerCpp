#include <iostream>

#include <libserver/socket.hpp>

int main() {
  server::SocketManager socket_("127.0.0.1", 5000);

  socket_.reconnectClient();
  socket_.waitData();

  return 0;
}