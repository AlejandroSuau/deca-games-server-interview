#pragma once

#include <unordered_set>


class CharacterEquipmentLoader {
public:
    CharacterEquipmentLoader();

    int LoadItemIds(std::string username, std::string password);

    const std::unordered_set<std::size_t>& GetItemIds() const;

private:
    std::unordered_set<std::size_t> item_ids_;

    int ParseAPIResponse(const char* xml_response);
};