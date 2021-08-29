#include "Class.h"

Class::Class() = default;

Class::Class(int class_id, int course_id, int time)
{
    this->course_id = course_id;
    this->class_id = class_id;
    this->time = time;
}

int Class::getClassId()
{
    return class_id;
}

int Class::getTime()
{
    return time;
}

void Class::addTime(int time)
{
    this->time += time;
}

int Class::getCourseId()
{
    return course_id;
}

bool Class::operator<(const Class c) const
{
    if (time < c.time)
    {
        return true;
    }
    else if (time > c.time)
    {
        return false;
    }
    else if (course_id > c.course_id)
    {
        return true;
    }
    else if (course_id < c.course_id)
    {
        return false;
    }
    else if (class_id > c.class_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Class::operator>(const Class c) const
{
    if (time > c.time)
    {
        return true;
    }
    else if (time < c.time)
    {
        return false;
    }
    else if (course_id < c.course_id)
    {
        return true;
    }
    else if (course_id > c.course_id)
    {
        return false;
    }
    else if (class_id < c.class_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Class::operator==(const Class c) const
{
    return c.class_id == class_id && c.course_id == course_id;
}

Class::Class(Class const &c)
{
    this->time = c.time;
    this->class_id = c.class_id;
    this->course_id = c.course_id;
}

int Class::GetHash()
{
    return this->class_id;
}

bool Class::operator!=(const Class c) const
{
    return !(*this == c);
}

