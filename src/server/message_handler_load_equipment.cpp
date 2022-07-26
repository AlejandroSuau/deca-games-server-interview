#include "message_handler_load_equipment.h"

#include <assert.h>
#include <string_view>

#include "local_equipment.h"
#include "equipment_loader.h"
#include "equipment_loader_exceptions.h"


MessageHandlerLoadEquipment::MessageHandlerLoadEquipment()
    : MessageHandler("^load ([\\w-\\.]+@(?:[\\w-]+\\.)+[\\w-]{2,4}) ([\\w]+)(?:\\s\r\n)?$") {}

void MessageHandlerLoadEquipment::FillResponseMessage(
        const std::smatch& matches, std::string& response) {
    const std::string username = matches[1].str();
    const std::string password = matches[2].str();
    std::unordered_set<std::size_t> loaded_items_ids;
    
    try {
        CharacterEquipmentLoader::GetInstance().LoadItemIds(
            username, password, loaded_items_ids);
        
        const auto& local_items_map 
            = LocalEquipment::GetInstance().GetItemIdNameUnorderedMap();
        bool did_match_any_item = false;
        const std::string_view separator = ",";
        for (const auto item_id : loaded_items_ids) {
            const auto item_found = local_items_map.find(item_id);
            if (item_found == local_items_map.end()) continue;

            if (did_match_any_item) response += separator.data();
            response += item_found->second;
            did_match_any_item = true;
        }

        if (!did_match_any_item) response += "No matching items";
    } catch(ExceptionCharacterEquipmentLoader e) {
        response = e.what();
    } catch(...) {
        assert(false && "Unexpected app behaviour");
    }
}       
        