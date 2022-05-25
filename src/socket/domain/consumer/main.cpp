#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int sock = 0, valread, client_fd;
    const char* hello = "Hello from client";
    const char* socket_path = "local.sock";
    struct sockaddr_un address;
    char buffer[1024] = { 0 };

    // Creating socket file descriptor
    if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("\nCould not create socket \n");
        return 1;
    }

    // Setting socket address information
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, socket_path, strlen(socket_path)+1);
    printf("%s: %d\n", socket_path, strlen(socket_path));

    // Connection to domain socket
    int size = offsetof(struct sockaddr_un, sun_path) + strlen(address.sun_path);
    if (client_fd = connect(sock, (struct sockaddr *)&address, size) == -1)
    {
       perror("\nConnection failed \n");
       return 1;
    }
    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(sock, buffer, 1024);
    printf("%s\n", buffer);

    // closing the connected socket
    close(client_fd);
    return 0;
}
