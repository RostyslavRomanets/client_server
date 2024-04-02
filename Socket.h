//
// Created by Rostik on 4/2/2024.
//

#pragma once

#include <unistd.h>
#include <stdexcept>

class Socket {
public:
    explicit Socket(int s) : m_socket(s) {
        if (m_socket < 0)
            throw std::runtime_error("Socket exception");
    }

    explicit operator int() const {
        return m_socket;
    }

    ~Socket() {
        close(m_socket);
    }

private:
    int m_socket;
};
