#include "message_handler_load_equipment.h"

#include <sstream>

#include "local_equipment.h"


MessageHandlerLoadEquipment::MessageHandlerLoadEquipment()
    : regex_("^load ([\\w-\\.]+@(?:[\\w-]+\\.)+[\\w-]{2,4}) ([\\w]+) (?:\r\n)?$") {}

std::string MessageHandlerLoadEquipment::GetResponseToMessage(
        std::string message) {
    std::smatch matches;
    if (!std::regex_search(message, matches, regex_))
        return "No matching pattern";

    std::string username = matches[1].str();
    std::string password = matches[2].str();
    // TODO: Should check "LoadItemIds" result. Maybe status_code error.
    character_equipment_loader_.LoadItemIds(username, password);
    const auto item_ids = character_equipment_loader_.GetItemIds();

    const auto matching_item_names = LocalEquipment::GetInstance().GetItemNames(
        item_ids);
    std::stringstream item_names;
    for (std::size_t i = 0; i < matching_item_names.size(); ++i) {
        if (i > 0) item_names << ", ";
        item_names << matching_item_names[i];
    }

    return item_names.str();
}