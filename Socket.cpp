#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <cstring>
#include <stdexcept>

#include "common_Socket.h"
#include "common_SocketExcept.h"

#define LISTEN_QUEUE_SIZE 10

Socket::Socket(Socket &&other) : fd(other.fd) { // Para el accept
  other.fd = -1;
}

Socket& Socket::operator=(Socket &&other) {
  this->fd = other.fd;
  other.fd = -1;
  return *this;
}

Socket::Socket(int file_des) : fd(file_des) {}

Socket::Socket() {}

Socket::~Socket() {
  if (fd != -1) {
    shutdown(fd, SHUT_RDWR);
    close(fd);
  }
}

void Socket::s_connect(const char* host, const char* service) {
  struct addrinfo *adr_l, *ptr;
  get_addr_list(&adr_l, host, service, 0);
  bool connected = false;
  int status = 0;
  for ( ptr=adr_l; !connected && ptr; ptr = ptr->ai_next ) {
    fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (fd == -1) {
      fprintf(stderr, "Socket error: %s\n", strerror(errno));
    } else {
      status = connect(fd, ptr->ai_addr, ptr->ai_addrlen);
      if (status == -1) {
        fprintf(stderr, "Connect error: %s\n", strerror(errno));
      }
      connected = (status == 0); // 0 --> Todo bien
    }
  }
  freeaddrinfo(adr_l);
  if (!connected) {
    throw SocketException("No connect on end of addrlist");
  }
}

void Socket::get_addr_list(struct addrinfo **addr_list,
    const char* host, const char* service, int ai_flags) {
  int status = 0;
  struct addrinfo hints;
  std::memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_flags = ai_flags;
  hints.ai_socktype = SOCK_STREAM;

  if ((status = getaddrinfo(host, service, &hints, addr_list)) != 0) {
      throw SocketException(gai_strerror(status));
  }
}

void Socket::s_bind(const char* serv) {
  struct addrinfo *adr_l, *ptr;
  int status;
  int val = 1;
  bool binded = false;
  get_addr_list(&adr_l, NULL, serv, AI_PASSIVE);

  for ( ptr=adr_l; !binded && ptr; ptr = ptr->ai_next ) {
    fd = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (fd == -1) {
      fprintf(stderr, "Socket error: %s\n", strerror(errno));
    } else {
      setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
      status = bind(fd, ptr->ai_addr, ptr->ai_addrlen);
      if (status == -1) {
        fprintf(stderr, "Binding error: %s\n", strerror(errno));
      }
      binded = (status == 0); // 0 --> Todo bien
    }
  }
  freeaddrinfo(adr_l);
  if (!binded) {
    throw SocketException("No bind on end of addrlist");
  }
}

void Socket::s_listen() {
  if ( listen(fd, LISTEN_QUEUE_SIZE) == -1 ) {
    throw SocketException("Error en listen");
  }
}

Socket Socket::s_accept() {
  int new_fd = accept(fd, NULL, NULL);
  if (new_fd == -1) {
    throw SocketException("Error al aceptar");
  }
  return Socket(new_fd);
}

void Socket::s_send(const char* msg, size_t length) {
  size_t bytes_sent = 0;
  int s;
  while ( bytes_sent < length ) {
    s = send(fd, msg + bytes_sent, length - bytes_sent, MSG_NOSIGNAL);
    if (s == 0) {
      break;
    } else if (s < 0) {
      throw SocketException("Error al mandar");
    } else {
      bytes_sent += s;
    }
  }
}

void Socket::s_recv(char* buffer, size_t length) {
  size_t bytes_recv = 0;
  int s;
  while ( bytes_recv < length ) {
    s = recv(fd, buffer + bytes_recv, length - bytes_recv, 0);
    if (s == 0) {
      break;
    } else if (s < 0) {
      throw SocketException("Error al recibir");
    } else {
      bytes_recv += s;
    }
  }
}

void Socket::shutdown_close() {
  shutdown(fd, SHUT_RDWR);
  close(fd);
}
