#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT_LEN 6

#define BUF_SIZE 500

void usage(char **argv) {
  printf("Usage:\n   %s <IP> <PORT>\n", argv[0]);
}

struct addrinfo create_default_addr_hints() {
  struct addrinfo *hints = (struct addrinfo *)malloc(sizeof(struct addrinfo));
  hints->ai_family   = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_protocol = IPPROTO_TCP;
  hints->ai_flags    = 0;
  return *hints;
}

void scan_port(const char *ip_addr, const char *port) {
  struct addrinfo hints = create_default_addr_hints();
  struct addrinfo *host_info = (struct addrinfo *)malloc(sizeof(struct addrinfo));
  int result = getaddrinfo(ip_addr, port, &hints, &host_info);
  if (result != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
    exit(EXIT_FAILURE);
  }

  int sockfd = socket(host_info->ai_family, host_info->ai_socktype, host_info->ai_protocol);
  if (sockfd != -1) {
    int result = connect(sockfd, host_info->ai_addr, host_info->ai_addrlen);
    if (result != -1)
      printf("port %s open\n", port);
    else
      printf("port %s closed\n", port);
  }
}

char *resolve_host(const char *__remote_host) {
  struct hostent *remote_host = gethostbyname(__remote_host);
  if (remote_host == NULL) {
    printf("Couldn't resolve host [%s]\n", __remote_host);
    exit(EXIT_FAILURE);
  }
  struct in_addr *remote_addr = (struct in_addr *)remote_host->h_addr;
  return inet_ntoa(*remote_addr);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    usage(argv);
    exit(EXIT_FAILURE);
  }
  
  char *remote_ip = resolve_host(argv[1]);
  char *port      = argv[2];
  scan_port(remote_ip, port);
  
  return 0;
}
