#pragma once

#include <string>

// #define this before any windows headers are included
#define _WIN32_WINNT _WIN32_WINNT_WIN10 // Windows 10.0
#include <Ws2tcpip.h>
#pragma comment( lib, "Ws2_32.lib" ) // link with Ws2_32.lib

#include "message_handler_load_equipment.h"

#define MAX_BUFFER_SIZE 4096


class Server {
public:
    Server(const std::string ip_address, const int port);
    ~Server();

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    bool Init();
    void Listen();
    void Cleanup();

private:
    const std::string ip_address_;
    const int port_;
    MessageHandlerLoadEquipment message_handler_;

    SOCKET CreateListeningSocket();
};