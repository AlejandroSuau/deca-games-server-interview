#pragma once

#include <unordered_set>
#include <unordered_map>


class LocalEquipment {
public:
    LocalEquipment(const LocalEquipment&) = delete;
    LocalEquipment& operator=(const LocalEquipment&) = delete;

    static const LocalEquipment& GetInstance();

    std::vector<std::string> GetItemNames(
        const std::unordered_set<std::size_t>& item_ids) const;

private:
    LocalEquipment();
    
    std::unordered_map<std::size_t, std::string> item_id_name_map_;
};