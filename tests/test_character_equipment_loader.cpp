#include "gtest/gtest.h"

#include <unordered_set>
#include <string_view>

#include "equipment_loader.h"
#include "equipment_loader_exceptions.h"


TEST(CharacterEquipmentLoaderTests, AccountNotFound) {
    const std::string_view username{"Alejandro"};
    const std::string_view password{"DECAGamesEmployer"};
    std::unordered_set<std::size_t> item_ids;
    EXPECT_THROW({
        CharacterEquipmentLoader::LoadItemIds(username, password, item_ids);
    }, ExceptionAccountNotFound);
}

TEST(CharacterEquipmentLoaderTests, EquipmentIsLoadedOk) {
    const std::string_view username{"backend-testRTG@decagames.com"};
    const std::string_view password{"backendtestRTG1"};
    std::unordered_set<std::size_t> item_ids_expected = {2711, 2606, 2712};
    std::unordered_set<std::size_t> item_ids;
    CharacterEquipmentLoader::LoadItemIds(username, password, item_ids);
    
    EXPECT_EQ(item_ids, item_ids_expected);
}