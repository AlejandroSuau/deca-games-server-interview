#include "equipment_loader.h"
#include "equipment_loader_exceptions.h"

#include <cstdio>
#include <string>

#include <cpr/cpr.h>

#include "pugixml.hpp"


void CharacterEquipmentLoader::LoadItemIds(
        const std::string_view username,
        const std::string_view password,
        std::unordered_set<std::size_t>& item_ids) {
    cpr::Response api_response = cpr::Get(
        cpr::Url{"https://www.realmofthemadgod.com/char/listInfo"},
        cpr::Parameters{{"guid", username.data()}, {"password", password.data()}});

    if (api_response.status_code != 200)
        throw ExceptionAPIServerUnavailable();

    std::string parsed_result;
    ParseLoadedResult(api_response.text, parsed_result);

    const auto invalid_item_id = static_cast<std::size_t>(-1);
    const std::string_view parsed_result_view{parsed_result};
    const std::string_view delim = ",";
    std::size_t start = 0;
    while (start < parsed_result_view.size()) {
        const auto end = parsed_result_view.find_first_of(delim, start);
        if (start != end) {
            std::size_t item_id;
            sscanf_s(parsed_result_view.substr(start, end-start).data(),
                     "%zu",
                     &item_id);
            if (item_id != invalid_item_id) item_ids.insert(item_id);
        }

        if (end == std::string_view::npos) break;
        
        start = end + 1;
    }
}

void CharacterEquipmentLoader::ParseLoadedResult(const std::string_view xml_response,
                                                 std::string& parsed_result) {
    pugi::xml_document document;
    pugi::xml_parse_result parse_result = document.load_string(xml_response.data());
    if (!parse_result)
        throw ExceptionUnexpectedXMLFormat();

    if (!document.child("Error").text().empty())
        throw ExceptionAccountNotFound();

    pugi::xml_node equipment_node = document.select_node(
        "//Chars/Char[1]/Equipment").node();
    parsed_result = equipment_node.first_child().value();
}

