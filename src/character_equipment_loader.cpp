#include "character_equipment_loader.h"

#include <cstdio>
#include <unordered_set>

#include <cpr/cpr.h>

#include "pugixml.hpp"


void CharacterEquipmentLoader::LoadItemIds(
        const std::string& username,
        const std::string& password,
        std::unordered_set<std::size_t>& item_ids) {
    cpr::Response api_response = cpr::Get(
        cpr::Url{"https://www.realmofthemadgod.com/char/listInfo"},
        cpr::Parameters{{"guid", username}, {"password", password}});

    if (api_response.status_code != 200)
        throw std::runtime_error("API Server is unavailable");

    std::string equipment_string;
    ParseLoadedResult(api_response.text.c_str(), equipment_string);
    
    const auto invalid_item_id = static_cast<std::size_t>(-1);
    const std::string delimiter = ",";
    std::size_t pos = 0;
    while ((pos = equipment_string.find(delimiter)) != std::string::npos) {
        std::size_t item_id;
        sscanf_s(equipment_string.substr(0, pos).c_str(), "%zu", &item_id);
        if (item_id != invalid_item_id) item_ids.insert(item_id);

        equipment_string.erase(0, pos + delimiter.length());
    }
}

void CharacterEquipmentLoader::ParseLoadedResult(const char* xml_response,
                                                 std::string& parsed_result) {
    pugi::xml_document document;
    pugi::xml_parse_result parse_result = document.load_string(xml_response);
    if (!parse_result)
        throw std::runtime_error("Unexpected XML format");

    if (!document.child("Error").text().empty())
        throw std::runtime_error("Account not found");

    pugi::xml_node equipment_node = document.select_node(
        "//Chars/Char[1]/Equipment").node();
    parsed_result = equipment_node.first_child().value();
}

