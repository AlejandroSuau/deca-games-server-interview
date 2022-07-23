#pragma once

#include <string_view>
#include <memory>

// Should define this variable to avoid:
// error: 'inet_pton' was not declared in this scope;
#define _WIN32_WINNT _WIN32_WINNT_WIN10
#include <Ws2tcpip.h>
#pragma comment( lib, "Ws2_32.lib" )

#include "message_handler.h"

#define MAX_BUFFER_SIZE 4096


class Server {
public:
    Server(const std::string_view ip_address,
           const int port);
    ~Server();

    Server(const Server&) noexcept = delete;
    Server& operator=(const Server&) = delete;

    Server(Server&&) noexcept = delete;
    Server& operator=(Server&&) = delete;

    bool Init();
    void Listen();
    void Cleanup();

private:
    const std::string_view ip_address_;
    const int port_;
    std::unique_ptr<MessageHandler> message_handler_;

    SOCKET CreateListeningSocket();
};