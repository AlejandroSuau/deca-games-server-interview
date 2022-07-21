#pragma once

#include <string>
#include <regex>
#include <unordered_set>
#include <sstream>


class MessageHandlerLoadEquipment {
public:
    MessageHandlerLoadEquipment();
    
    MessageHandlerLoadEquipment(const MessageHandlerLoadEquipment&) = delete;
    MessageHandlerLoadEquipment& operator=(const MessageHandlerLoadEquipment&) = delete;

    void FillResponseToMessage(const std::string& message, std::string& response);

private:
    const std::regex regex_;

    void FillStreamWithMatchingItemNames(
        std::ostringstream& ss,
        const std::unordered_set<std::size_t>& item_ids);
};