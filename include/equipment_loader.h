#pragma once

#include <unordered_set>
#include <string>
#include <sstream>


class CharacterEquipmentLoader {
public:
    static void LoadItemIds(const std::string& username, 
                            const std::string& password,
                            std::unordered_set<std::size_t>& item_ids);

private:    
    static void ParseLoadedResult(const char* xml_response,
                                  std::stringstream& parsed_result);
};