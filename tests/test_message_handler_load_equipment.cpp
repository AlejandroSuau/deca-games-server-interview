#include "gtest/gtest.h"

#include <string>
#include <sstream>

#include "message_handler_load_equipment.h"


TEST(MessageHandlerLoadEquipmentTests, WrongMessageFormat) {
    MessageHandlerLoadEquipment message_handler;
    const std::string message = "This is a wrong message format";
    std::string response;
    message_handler.FillResponseToMessage(message, response);

    std::string expected_response = "Wrong message format";
    ASSERT_EQ(response, expected_response);
}

TEST(MessageHandlerLoadEquipmentTests, FormatIsOk) {
    MessageHandlerLoadEquipment message_handler;
    const std::string message = "load backend-testRTG@decagames.com backendtestRTG1";
    std::string response;
    message_handler.FillResponseToMessage(message, response);

    std::unordered_set<std::string> item_names_expected = {
        "Energy Staff", "Fire Spray Spell", "Firebrand Staff" 
    };

    std::stringstream response_ss(response);
    const auto invalid_item_id = static_cast<std::size_t>(-1);
    bool all_item_names_found = true;
    while(response_ss.good() && all_item_names_found) {
        std::string item_name;
        getline(response_ss, item_name, ',');

        const bool is_expected_item = (
            item_names_expected.find(item_name) != item_names_expected.end());
        if (item_name.empty() || !is_expected_item) {
            all_item_names_found = false;
        }
    }

    ASSERT_TRUE(all_item_names_found);
}
