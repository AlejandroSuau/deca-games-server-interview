#pragma once

#include <unordered_set>


class CharacterEquipmentLoader {
public:
    static void LoadItemIds(const std::string& username, 
                            const std::string& password,
                            std::unordered_set<std::size_t>& item_ids);

private:    
    static void ParseLoadedResult(const char* xml_response,
                                  std::string& parsed_result);
};