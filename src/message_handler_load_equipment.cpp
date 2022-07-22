#include "message_handler_load_equipment.h"

#include <assert.h>

#include "local_equipment.h"
#include "character_equipment_loader.h"


MessageHandlerLoadEquipment::MessageHandlerLoadEquipment()
    : regex_("^load ([\\w-\\.]+@(?:[\\w-]+\\.)+[\\w-]{2,4}) ([\\w]+)(?:\\s\r\n)?$") {}

void MessageHandlerLoadEquipment::FillResponseToMessage(
        const std::string& message, std::string& response) {
    std::smatch matches;
    if (!std::regex_search(message, matches, regex_)) {
        response = "Wrong message format";
        return;
    }

    const std::string username = matches[1].str();
    const std::string password = matches[2].str();
    std::unordered_set<std::size_t> loaded_items_ids;
    
    try {
        CharacterEquipmentLoader::LoadItemIds(
            username, password, loaded_items_ids);
        
        std::ostringstream response_message;
        FillStreamWithMatchingItemNames(response_message, loaded_items_ids);
        response = response_message.str();
    } catch(ExceptionCharacterEquipmentLoader e) {
        response = e.what();
    } catch(...) {
        assert(false && "Unexpected app behaviour");
    }
}

void MessageHandlerLoadEquipment::FillStreamWithMatchingItemNames(
        std::ostringstream& ss,
        const std::unordered_set<std::size_t>& item_ids) {
    const auto& local_items_map 
        = LocalEquipment::GetInstance().GetItemIdNameUnorderedMap();
    bool did_match_item = false;
    for (const auto item_id : item_ids) {
        const auto item_found = local_items_map.find(item_id);
        if (item_found == local_items_map.end()) continue;

        if (did_match_item) ss << ",";            
        ss << item_found->second;
        did_match_item = true;
    }

    if (!did_match_item) ss << "No matching items";
}
       
        
        