#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Socket.h"

#define PORT 8080

int main() {
    try
    {
        sockaddr_in address{ AF_INET, htons(PORT) };

        Socket client(socket(AF_INET, SOCK_STREAM, 0));

        inet_pton(AF_INET, "127.0.0.1", &address.sin_addr);

        auto status = connect(static_cast<int>(client), reinterpret_cast<sockaddr *>(&address), sizeof(address));
        if (status < 0)
            throw std::runtime_error("Connect exception");

        char buf[1024] {};
        std::string msg = "test";
        send(static_cast<int>(client), msg.c_str(), msg.size(), 0);
        read(static_cast<int>(client), buf, sizeof(buf));

        std::cout << "Send message: " << msg << std::endl;
        std::cout << "Respond: " << buf << std::endl;

        msg = "hello";
        send(static_cast<int>(client), msg.c_str(), msg.size(), 0);
        read(static_cast<int>(client), buf, sizeof(buf));

        std::cout << "Send message: " << msg << std::endl;
        std::cout << "Respond: " << buf << std::endl;
    }
    catch (const std::exception& ex)
    {
        perror(ex.what());
    }
}
