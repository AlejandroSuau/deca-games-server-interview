#pragma once

#include <string>
#include <regex>

#include "character_equipment_loader.h"


class MessageHandlerLoadEquipment {
public:
    MessageHandlerLoadEquipment();

    std::string GetResponseToMessage(std::string message);

private:
    const std::regex regex_;
    CharacterEquipmentLoader character_equipment_loader_;
};