#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT_LENGTH

void usage(char **argv) {
  printf("Usage:\n   %s <IP> [PORT]\n", argv[0]);
}

struct addrinfo create_default_addr_hints() {
  struct addrinfo hints = { 0 };
  hints.ai_family   = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags    = 0;
  return hints;
}

int is_open_port(const char *ip_addr, const char *port) {
  struct addrinfo hints = create_default_addr_hints();
  struct addrinfo *host_info;
  int result = getaddrinfo(ip_addr, port, &hints, &host_info);
  if (result != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(result));
    exit(EXIT_FAILURE);
  }

  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sockfd != -1) {
    int result = connect(sockfd, host_info->ai_addr, host_info->ai_addrlen);
    if (result != -1) {
      close(sockfd);
      return 1;
    }
    else {
      close(sockfd);
      return 0;
    }
  }
  return -1;
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
  if (argc == 2) {
    char *remote_ip = resolve_host(argv[1]);
    for(int i = 1; i < 65536; i++) {
      char port[5];
      snprintf(port, 6, "%d", i);
      if (is_open_port(remote_ip, port) == 1) {
	printf("%s/tcp open\n", port);
      }
    }
  }
  else if (argc == 3) {
    char *remote_ip = resolve_host(argv[1]);
    char *port = argv[2];
    if (is_open_port(remote_ip, port) == 1) {
      printf("%s/tcp open\n", port);
    }
    else {
      printf("%s/tcp closed\n", port);
    }
  }
  else {
    usage(argv);
    exit(EXIT_FAILURE);
  }
  
  return 0;
}
