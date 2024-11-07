#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

#define DEFAULT_PORT 46645
#define LISTEN_BACKLOG 5
#define BUFFER_SIZE 1024

void *handleConnection(int *a_client)
{
    int socket_fd = *(int *)a_client;
    printf("conneted to %d\n", socket_fd);

    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    int bytes_read = read(socket_fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);
    write(socket_fd, buffer, bytes_read);
    int res = strncmp("exit", buffer, 4);
    printf("res: %d\n", res);

    printf("done with %d\n", socket_fd);

    // return res;
}

int main(int argc, char *argv[])
{
    int port = DEFAULT_PORT;

    if (argc > 2 && strcmp(argv[1], "-p") == 0)
    {
        port = atoi(argv[2]);
    }

    // create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // set up server address
    struct sockaddr_in server_address;
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(port);

    int returnVal;
    // bind socket to server address
    returnVal = bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address));
    // listen for connetions
    returnVal = listen(server_fd, LISTEN_BACKLOG);

    // printf("Server ip is %d\n", server_address.sin_addr.s_addr);
    printf("Server listening on port %d\n", port);

    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    while (1)
    {
        int client_fd;
        pthread_t thread;

        client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_address_len);
        int *client_fd_ptr = &client_fd;
        if (client_fd < 0)
        {
            perror("Accept failed");
            continue;
        }

        pthread_create(&thread, NULL, (void *)handleConnection, client_fd_ptr);

        // handleConnection(client_fd);
        close(client_fd);
    }
    close(server_fd);

    return 0;
}