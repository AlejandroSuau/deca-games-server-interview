#pragma once

#include <regex>
#include <string>


class MessageHandler {
public:
    MessageHandler(const std::string& regex_pattern);
    virtual ~MessageHandler() = default;

    MessageHandler(const MessageHandler&) = delete;
    MessageHandler& operator=(const MessageHandler&) = delete;

    MessageHandler(MessageHandler&&) = delete;
    MessageHandler& operator=(MessageHandler&&) = delete;

    void ResponseToMessage(const std::string& message, std::string& response);

protected:
    std::regex regex_;

    virtual void FillResponseMessage(
        const std::smatch& matches, std::string& response) = 0;
};