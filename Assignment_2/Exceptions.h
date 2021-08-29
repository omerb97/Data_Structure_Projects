#ifndef WET1_EXCEPTIONS_H
#define WET1_EXCEPTIONS_H

#include <iostream>
#include <string>

class Exception : public std::exception
{
public:
    const char *what() const noexcept override;
};

class InitFail : public Exception
{
public:
    const char *what() const noexcept override;
};

class InvalidInputs : public Exception
{
public:
    const char *what() const noexcept override;
};

class ValueExists : public Exception
{
public:
    const char *what() const noexcept override;
};

class ValueNoExist : public Exception
{
public:
    const char *what() const noexcept override;
};

class TooManyClasses : public Exception
{
public:
    const char *what() const noexcept override;
};

#endif
