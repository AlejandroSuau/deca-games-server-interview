#include "equipment_loader_exceptions.h"


ExceptionCharacterEquipmentLoader::ExceptionCharacterEquipmentLoader(
    const std::string& what_arg) : std::runtime_error(what_arg) {}

ExceptionAPIServerUnavailable::ExceptionAPIServerUnavailable()
    : ExceptionCharacterEquipmentLoader("DECA API Server is not available") {}

ExceptionAccountNotFound::ExceptionAccountNotFound()
    : ExceptionCharacterEquipmentLoader("Account not found") {}

ExceptionUnexpectedXMLFormat::ExceptionUnexpectedXMLFormat()
    : ExceptionCharacterEquipmentLoader("Unexpected XML Format") {}