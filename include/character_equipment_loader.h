#pragma once

#include <unordered_set>
#include <string>
#include <sstream>


class ExceptionCharacterEquipmentLoader : public std::runtime_error {
public:
    explicit ExceptionCharacterEquipmentLoader(const std::string& what_arg)
        : std::runtime_error(what_arg) {}
};
class ExceptionAPIServerUnavailable : public ExceptionCharacterEquipmentLoader {
public:
    explicit ExceptionAPIServerUnavailable()
        : ExceptionCharacterEquipmentLoader("DECA API Server is not available") {}
};
class ExceptionAccountNotFound : public ExceptionCharacterEquipmentLoader {
public:
    explicit ExceptionAccountNotFound()
        : ExceptionCharacterEquipmentLoader("Account not found") {}
};
class ExceptionUnexpectedXMLFormat : public ExceptionCharacterEquipmentLoader {
public:
    explicit ExceptionUnexpectedXMLFormat()
        : ExceptionCharacterEquipmentLoader("Unexpected XML Format") {}
};

class CharacterEquipmentLoader {
public:
    static void LoadItemIds(const std::string& username, 
                            const std::string& password,
                            std::unordered_set<std::size_t>& item_ids);

private:    
    static void ParseLoadedResult(const char* xml_response,
                                  std::stringstream& parsed_result);
};