#ifndef SOCKET_H
#define SOCKET_H

#include <string>

class Socket {
private:
  int fd;

public:
  explicit Socket(int file_des);

  Socket(); // Para que no me lo pise el otro

  ~Socket();

  Socket(const Socket &other) = delete; // Dont

  Socket& operator=(const Socket &other) = delete;

  Socket(Socket &&other);

  Socket& operator=(Socket &&other);

  void connect(const char* host, const char* service);

  void bind(const char* serv);

  void listen();

  Socket accept();

  void send(const char* msg, size_t length);

  int recv(char* buffer, size_t length);

  void shutdown_close();

private:
void get_addr_list(struct addrinfo **addr_list, const char* host,
                         const char* service, int ai_flags);
};

#endif
