#include "local_equipment.h"

#include <filesystem>
#include <assert.h>

#include "pugixml.hpp"


LocalEquipment::LocalEquipment() {
    pugi::xml_document document_;
    std::string filename = std::filesystem::current_path().u8string();
    filename += "\\equip.xml";
    pugi::xml_parse_result parse_result = document_.load_file(filename.c_str());
    if (!parse_result) assert(false && "equip.xml could not be loaded.");

    pugi::xpath_node_set items = document_.select_nodes("Objects/Object");
    for (const auto node : items) {
        const auto item = node.node();
        const auto* item_id_in_hex = item.attribute("type").value();
        const std::size_t item_id = strtoul(item_id_in_hex, NULL, 16);
        item_id_name_unordered_map_.insert(
            {item_id, item.attribute("id").value()});
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