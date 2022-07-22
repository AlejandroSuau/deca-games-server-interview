#include "local_equipment.h"

#include <assert.h>

#include "pugixml.hpp"


LocalEquipment::LocalEquipment() {
    pugi::xml_document document_;
    pugi::xml_parse_result parse_result = document_.load_file("bin/equip.xml");
    if (!parse_result) assert(false && "equip.xml could not be loaded.");

    pugi::xpath_node_set items = document_.select_nodes("Objects/Object");
    for (const auto node : items) {
        const auto item = node.node();
        const char* item_id_in_hex = item.attribute("type").value();
        const std::size_t item_id = strtoul(item_id_in_hex, NULL, 16);
        const char* item_name = item.attribute("id").value();
        item_id_name_unordered_map_.insert({item_id, item_name});
    }
}

const LocalEquipment& LocalEquipment::GetInstance() {
    static LocalEquipment local_equipment;
    return local_equipment;
}

const LocalEquipment::ItemIdNameUnorderedMap&
LocalEquipment::GetItemIdNameUnorderedMap() const {
    return item_id_name_unordered_map_;
}