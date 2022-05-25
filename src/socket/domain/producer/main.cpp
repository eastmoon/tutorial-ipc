#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_un address;
    const char* socket_path = "local.sock";
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    const char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting socket address information
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, socket_path, strlen(socket_path)+1);
    printf("%s: %d\n", address.sun_path, strlen(socket_path));

    // Connection to domain socket and setting listen
    int size = offsetof(struct sockaddr_un, sun_path) + strlen(address.sun_path);
    if (bind(server_fd, (struct sockaddr*)&address, size) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);
    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // sleep 1s
    sleep(1);
    // closing the connected socket
    close(new_socket);
    // closing the listening socket
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
