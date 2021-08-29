#include "Exceptions.h"

const char* Exception::what() const noexcept
{
    return "Unknown error";
}

const char* InitFail::what() const noexcept
{
    return "Initialization failed";
}

const char* InvalidInputs::what() const noexcept
{
    return "One of the inputs has an invalid value";
}
const char* TreeValueExists::what() const noexcept
{
    return "This value already exists in the tree";
}

const char* TreeValueNoExist::what() const noexcept
{
    return "This value does not exist in this tree";
}

const char* TooManyClasses::what() const noexcept
{
    return "This value does not exist in this tree";
}

