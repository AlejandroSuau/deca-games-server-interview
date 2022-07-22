#include "gtest/gtest.h"

#include <unordered_set>
#include <string>

#include "character_equipment_loader.h"


TEST(CharacterEquipmentLoaderTests, AccountNotFound) {
    const std::string username = "Alejandro";
    const std::string password = "DECAGamesEmployer";
    std::unordered_set<std::size_t> item_ids;
    EXPECT_THROW({
        CharacterEquipmentLoader::LoadItemIds(username, password, item_ids);
    }, ExceptionAccountNotFound);
}

TEST(CharacterEquipmentLoaderTests, EquipmentIsLoadedOk) {
    const std::string username = "backend-testRTG@decagames.com";
    const std::string password = "backendtestRTG1";
    std::unordered_set<std::size_t> item_ids_expected = {2711, 2606, 2712};
    std::unordered_set<std::size_t> item_ids;
    CharacterEquipmentLoader::LoadItemIds(username, password, item_ids);
    
    EXPECT_EQ(item_ids, item_ids_expected);
}