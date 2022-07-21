#include "local_equipment.h"

#include <assert.h>

#include "pugixml.hpp"

// We assume that the equip.xml has a correct structure.
// In addition, the code will end execution with a fail assert
// is the equip.xml is not found.

LocalEquipment::LocalEquipment() {
    pugi::xml_document document_;
    pugi::xml_parse_result parse_result = document_.load_file("bin/equip.xml");
    if (!parse_result) assert(false);

    pugi::xpath_node_set items = document_.select_nodes("Objects/Object");
    for (const auto node : items) {
        const auto item = node.node();
        const char* item_id_in_hex = item.attribute("type").value();
        const std::size_t item_id = strtoul(item_id_in_hex, NULL, 16);
        const char* item_name = item.attribute("id").value();
        item_id_name_map_.insert({item_id, item_name});
    }
}

const LocalEquipment& LocalEquipment::GetInstance() {
    static LocalEquipment local_equipment;
    return local_equipment;
}

std::vector<std::string> LocalEquipment::GetItemNames(
        const std::unordered_set<std::size_t>& item_ids) const {
    std::vector<std::string> item_names;
    for (const auto item_id : item_ids) {
        const auto item_found = item_id_name_map_.find(item_id);
        if (item_found != item_id_name_map_.end())
            item_names.push_back(item_found->second);
    }

    return item_names;
}