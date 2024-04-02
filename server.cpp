//
// Created by Rostik on 4/2/2024.
//

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <cstring>

#include "Socket.h"

#define PORT 8080

void worker(int session_fd)
{
    try
    {
        Socket session(session_fd);
        char buf[1024]{};

        while (true)
        {
            auto bytes = read(static_cast<int>(session), buf, 1024);

            if (bytes < 0)
                throw std::runtime_error("Read exception");
            if (bytes == 0)
                return;

            if (strcmp(buf, "hello") == 0)
                send(static_cast<int>(session), "world", 5, 0);
            else
                send(static_cast<int>(session), buf, bytes, 0);
        }
    }
    catch (const std::exception& ex)
    {
        perror(ex.what());
    }
}

int main()
{
    try
    {
        sockaddr_in address { AF_INET, htons(PORT), INADDR_ANY };
        socklen_t addrlen = sizeof(address);

        Socket server(socket(AF_INET, SOCK_STREAM, 0));

        if (bind(static_cast<int>(server), reinterpret_cast<const sockaddr *>(&address), sizeof(address)) < 0)
            throw std::runtime_error("Bind exception");

        if (listen(static_cast<int>(server), 1) < 0)
            throw std::runtime_error("Listen exception");

        while (true)
        {
            int session_fd = accept(static_cast<int>(server), reinterpret_cast<sockaddr *>(&address), &addrlen);
            if (session_fd < 0)
                throw std::runtime_error("Socket exception");

            std::thread(worker, session_fd).detach();
        }
    }
    catch (const std::exception& ex)
    {
        perror(ex.what());
    }
}
