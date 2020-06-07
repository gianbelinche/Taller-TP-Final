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

  void s_connect(const char* host, const char* service);

  void s_bind(const char* serv);

  void s_listen();

  Socket s_accept();

  void s_send(const char* msg, size_t length);

  void s_recv(char* buffer, size_t length);

  void shutdown_close();

private:
void get_addr_list(struct addrinfo **addr_list, const char* host,
                         const char* service, int ai_flags);
};

#endif
