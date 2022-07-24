#include "gtest/gtest.h"

#include <string>
#include <sstream>

#include "message_handler_load_equipment.h"


TEST(MessageHandlerLoadEquipmentTests, WrongMessageFormat) {
    MessageHandlerLoadEquipment message_handler;
    const std::string message = "This is a wrong message format";
    std::string response;
    message_handler.ResponseToMessage(message, response);

    std::string expected_response = "Wrong message format";
    ASSERT_EQ(response, expected_response);
}

TEST(MessageHandlerLoadEquipmentTests, FormatIsOk) {
    MessageHandlerLoadEquipment message_handler;
    const std::string message = "load backend-testRTG@decagames.com backendtestRTG1";
    std::string response;
    message_handler.ResponseToMessage(message, response);

    std::unordered_set<std::string> item_names_expected = {
        "Energy Staff", "Fire Spray Spell", "Firebrand Staff" 
    };

    std::size_t found_items = 0;
    std::istringstream response_ss(response);
    std::string item_name;
    while(std::getline(response_ss, item_name, ',')) {
        const bool is_expected_item = (
            item_names_expected.find(item_name) != item_names_expected.end());
        if (is_expected_item) ++found_items;
    }

    ASSERT_EQ(item_names_expected.size(), found_items);
}
