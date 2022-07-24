#pragma once

#include <unordered_set>
#include <string_view>
#include <sstream>


class CharacterEquipmentLoader {
public:
    static void LoadItemIds(const std::string_view username, 
                            const std::string_view password,
                            std::unordered_set<std::size_t>& item_ids);

private:    
    static void ParseLoadedResult(const std::string_view xml_response,
                                  std::stringstream& parsed_result);
};