#pragma once

#include <string>
#include <regex>
#include <unordered_set>
#include <sstream>

#include "message_handler.h"


class MessageHandlerLoadEquipment : public MessageHandler {
public:
    MessageHandlerLoadEquipment();
    ~MessageHandlerLoadEquipment() = default;
    
    MessageHandlerLoadEquipment(const MessageHandlerLoadEquipment&) noexcept = delete;
    MessageHandlerLoadEquipment& operator=(const MessageHandlerLoadEquipment&) = delete;

    MessageHandlerLoadEquipment(MessageHandlerLoadEquipment&&) noexcept = delete;
    MessageHandlerLoadEquipment& operator=(MessageHandlerLoadEquipment&&) = delete;

    void FillResponseMessage(
        const std::smatch& matches, std::string& response) override;
};