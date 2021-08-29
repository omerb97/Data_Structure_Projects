#include "Exceptions.h"

const char *Exception::what() const noexcept
{
    return "Unknown error";
}

const char *InitFail::what() const noexcept
{
    return "Initialization failed";
}

const char *InvalidInputs::what() const noexcept
{
    return "One of the inputs has an invalid value";
}

const char *ValueExists::what() const noexcept
{
    return "This value already exists in the database";
}

const char *ValueNoExist::what() const noexcept
{
    return "This value does not exist in this database";
}

const char *TooManyClasses::what() const noexcept
{
    return "This value does not exist in this tree";
}

