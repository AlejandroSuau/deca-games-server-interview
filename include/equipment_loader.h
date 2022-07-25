#pragma once

#include <unordered_set>
#include <string_view>
#include <sstream>


class CharacterEquipmentLoader {
public:
    CharacterEquipmentLoader(const CharacterEquipmentLoader&) noexcept = delete;
    CharacterEquipmentLoader& operator=(const CharacterEquipmentLoader&) = delete;

    CharacterEquipmentLoader(CharacterEquipmentLoader&&) noexcept = delete;
    CharacterEquipmentLoader& operator=(CharacterEquipmentLoader&&) = delete;

    static const CharacterEquipmentLoader& GetInstance();

    static void LoadItemIds(const std::string_view username, 
                            const std::string_view password,
                            std::unordered_set<std::size_t>& item_ids);
private:
    CharacterEquipmentLoader() = default;

    static void ParseLoadedResult(const std::string_view xml_response,
                                  std::unordered_set<std::size_t>& item_ids);
};