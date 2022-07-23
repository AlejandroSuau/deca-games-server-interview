#include "message_handler.h"


MessageHandler::MessageHandler(const std::string_view regex_pattern)
    : regex_(regex_pattern.data()) {}

void MessageHandler::ResponseToMessage(const std::string& message,
                                       std::string& response) {
    std::smatch matches;
    if (!std::regex_search(message, matches, regex_)) {
        response = "Wrong message format";
        return;
    }

    FillResponseMessage(matches, response);
}
