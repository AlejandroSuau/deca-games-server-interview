#include "character_equipment_loader.h"

#include <cpr/cpr.h>

#include "pugixml.hpp"


CharacterEquipmentLoader::CharacterEquipmentLoader() {}

int CharacterEquipmentLoader::LoadItemIds(std::string username,
                                          std::string password) {
    cpr::Response api_response = cpr::Get(
        cpr::Url{"https://www.realmofthemadgod.com/char/listInfo"},
        cpr::Parameters{{"guid", username}, {"password", password}});

    if (api_response.status_code == 200) {
        ParseAPIResponse(api_response.text.c_str());
    } else {

    }
    
    return 0;
}

int CharacterEquipmentLoader::ParseAPIResponse(const char* xml_response) {
    pugi::xml_document document;
    pugi::xml_parse_result parse_result = document.load_string(xml_response);
    if (!parse_result) return -1;

    pugi::xml_node equipment_node = document.select_node(
        "//Chars/Char[1]/Equipment").node();
    std::string equipment_string = equipment_node.first_child().value();

    const std::string delimiter = ",";
    std::size_t pos = 0;
    std::string token;
    while ((pos = equipment_string.find(delimiter)) != std::string::npos) {
        token = equipment_string.substr(0, pos);
        equipment_string.erase(0, pos + delimiter.length());
        if (token.compare("-1") != 0) {
            item_ids_.insert(strtoul(token.c_str(), NULL, 10));
        }
    }
}

const std::unordered_set<std::size_t>&
CharacterEquipmentLoader::GetItemIds() const {
    return item_ids_;
}
