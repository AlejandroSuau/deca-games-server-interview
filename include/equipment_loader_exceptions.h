#pragma once

#include <stdexcept>
#include <string>


class ExceptionCharacterEquipmentLoader : public std::runtime_error {
public:
    explicit ExceptionCharacterEquipmentLoader(const std::string& what_arg);
};

class ExceptionAPIServerUnavailable : public ExceptionCharacterEquipmentLoader {
public:
    explicit ExceptionAPIServerUnavailable();
};

class ExceptionAccountNotFound : public ExceptionCharacterEquipmentLoader {
public:
    explicit ExceptionAccountNotFound();
};

class ExceptionUnexpectedXMLFormat : public ExceptionCharacterEquipmentLoader {
public:
    explicit ExceptionUnexpectedXMLFormat();
};