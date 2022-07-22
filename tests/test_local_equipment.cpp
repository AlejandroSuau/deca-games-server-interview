#include "gtest/gtest.h"

#include <unordered_map>
#include <string>

#include "local_equipment.h"


TEST(LocalEquipmentTests, TestLocalEquipmentIsOk) {
    const auto& items_map 
        = LocalEquipment::GetInstance().GetItemIdNameUnorderedMap();
    
    const std::unordered_map<std::size_t, std::string> expected_items_map = {
        {2712, "Firebrand Staff"},
        {2606, "Fire Spray Spell"},
        {1770, "Aegis Armor"},
        {2711, "Energy Staff"},
        {8281, "Helm of the Tribune"},
        {20303, "2WizardST1"},
        {4058, "Mask of Anubis"}
    };

    EXPECT_EQ(items_map, expected_items_map);
}
