#pragma once

#include <unordered_map>
#include <string>


class LocalEquipment {
public:
    LocalEquipment(const LocalEquipment&) noexcept = delete;
    LocalEquipment& operator=(const LocalEquipment&) = delete;

    LocalEquipment(LocalEquipment&&) noexcept = delete;
    LocalEquipment& operator=(LocalEquipment&&) = delete;

    static const LocalEquipment& GetInstance();

    typedef std::unordered_map<std::size_t, std::string> ItemIdNameUnorderedMap;
    const ItemIdNameUnorderedMap& GetItemIdNameUnorderedMap() const;

private:
    LocalEquipment();
    
    ItemIdNameUnorderedMap item_id_name_unordered_map_;
};