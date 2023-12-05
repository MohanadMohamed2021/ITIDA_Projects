#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#define buffer_size (1024 * 10)  // 4k
#define socket_port      80
typedef struct sockaddr_in local_socket_addr_t;
typedef struct sockaddr socket_addr_t;

int main()
{
    local_socket_addr_t client_addr;
    char buffer[buffer_size];
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    client_addr.sin_family = AF_INET;
    client_addr.sin_port=htons(socket_port);
    inet_pton(AF_INET,"142.251.37.174",&(client_addr.sin_addr));
    int ret = connect(client_socket, (socket_addr_t *)&client_addr, sizeof(local_socket_addr_t));
    if (ret < 0)
    {
        perror("server is down.....");
        exit(EXIT_FAILURE);
    }
    strcpy(buffer,"GET / HTTP/1.1 \r\n\r\n");
    ret = write(client_socket, buffer, sizeof(buffer));
    if (ret < 0)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
    ret = read(client_socket, buffer , sizeof(buffer));
    if (ret < 0)
    {
        perror("write");
        exit(EXIT_FAILURE);
    }
    printf("%s",buffer);
    close(client_socket);
    return 0;
}