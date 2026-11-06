include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 9002

int main() {
    signal(SIGINT, SIG_DFL);
    int s = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in a = {.sin_family=AF_INET, .sin_addr.s_addr=INADDR_ANY, .sin_port=htons(PORT)};
    bind(s, (struct sockaddr*)&a, sizeof(a));
    listen(s, 10);
    printf("TCP server on port %d\n", PORT);
    while (1) {
        struct sockaddr_in c;
        socklen_t l = sizeof(c);
        int fd = accept(s, (struct sockaddr*)&c, &l);
        char ip[16];
        inet_ntop(AF_INET, &c.sin_addr, ip, 16);
        printf("connection received from %s:%d\n", ip, ntohs(c.sin_port));
        close(fd);
    }
}

