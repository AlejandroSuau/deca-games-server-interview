#include "server.h"

#include <string>

#include "message_handler_load_equipment.h"


Server::Server(const std::string_view ip_address, const int port) 
    : ip_address_(ip_address),
      port_(port),
      message_handler_(std::make_unique<MessageHandlerLoadEquipment>()) {}

Server::~Server() {
    Cleanup();
}

bool Server::Init() {
    WSAData data;
    WORD version = MAKEWORD(2, 2);
    int ws_init = WSAStartup(version, &data);

    return (ws_init == 0);
}

void Server::Listen() {
    char buffer[MAX_BUFFER_SIZE];

    while (true) {
        const SOCKET listening = CreateListeningSocket();
        if (listening == INVALID_SOCKET) break;

        const SOCKET client = accept(listening, nullptr, nullptr);
        if (client != INVALID_SOCKET) {
            closesocket(listening);

            int bytes_received;
            do {
                ZeroMemory(buffer, MAX_BUFFER_SIZE);

                bytes_received = recv(client, buffer, MAX_BUFFER_SIZE, 0);
                if (bytes_received > 0) {
                    std::string message = std::string(buffer, 0, bytes_received);
                    std::string response;
                    message_handler_->ResponseToMessage(message, response);

                    send(client, response.c_str(), response.size() + 1, 0);
                }
            } while (bytes_received > 0);
            closesocket(client);
        }
    }
}

void Server::Cleanup() {
    WSACleanup();
}

SOCKET Server::CreateListeningSocket() {
    SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == INVALID_SOCKET) return INVALID_SOCKET;

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port_);
    inet_pton(AF_INET, ip_address_.data(), &hint.sin_addr);

    int binding_res = bind(listening, (sockaddr*)&hint, sizeof(hint));
    if (binding_res != SOCKET_ERROR) {
        int listen_res = listen(listening, SOMAXCONN);
        if (listen_res != SOCKET_ERROR) return listening;
    }

    return INVALID_SOCKET;
}