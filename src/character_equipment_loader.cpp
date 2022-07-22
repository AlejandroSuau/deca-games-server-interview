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
        throw ExceptionAPIServerUnavailable();

    std::stringstream parsed_result_ss;
    ParseLoadedResult(api_response.text.c_str(), parsed_result_ss);
    
    const auto invalid_item_id = static_cast<std::size_t>(-1);
    while(parsed_result_ss.good()) {
        std::string token;
        getline(parsed_result_ss, token, ',');
        
        if (!token.empty()) {
            std::size_t item_id;
            sscanf_s(token.c_str(), "%zu", &item_id);
            if (item_id != invalid_item_id) item_ids.insert(item_id);
        }
    }
}

void CharacterEquipmentLoader::ParseLoadedResult(const char* xml_response,
                                                 std::stringstream& parsed_result) {
    pugi::xml_document document;
    pugi::xml_parse_result parse_result = document.load_string(xml_response);
    if (!parse_result)
        throw ExceptionUnexpectedXMLFormat();

    if (!document.child("Error").text().empty())
        throw ExceptionAccountNotFound();

    pugi::xml_node equipment_node = document.select_node(
        "//Chars/Char[1]/Equipment").node();
    parsed_result << equipment_node.first_child().value();
}

