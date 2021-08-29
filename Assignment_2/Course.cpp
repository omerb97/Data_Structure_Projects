#include "Course.h"

Course::Course(const Course &course)
{
    course_id = course.course_id;
    num_of_classes = course.num_of_classes;
    this->classes = new HashTable<Class>();

    for (int i = 0; i < num_of_classes; i++)
    {
        Class temp = Class(i, course_id, 0);
        classes->Insert(course.classes->Search(&temp)->GetData());
    }
}

Course::Course(int course_id)
{
    this->course_id = course_id;
    this->num_of_classes = 0;
    this->classes = new HashTable<Class>();
}

Course &Course::operator=(Course &other)
{
    course_id = other.course_id;
    num_of_classes = other.num_of_classes;

    if (this)
    {
        classes->~HashTable();
    }

    this->classes = new HashTable<Class>();

    for (int i = 0; i < num_of_classes; i++)
    {
        Class temp = Class(i, course_id, 0);
        classes->Insert((other.classes->Search(&temp)->GetData()));
    }

    return *this;
}

Course::~Course()
{
    delete classes;
}

Class *Course::getClass(int id)
{
    Class temp = Class(id, course_id, 0);
    return classes->Search(&temp)->GetData();
}

int Course::getCourseId()
{
    return course_id;
}

int Course::getNumOfClasses()
{
    return num_of_classes;
}

bool Course::operator<(const Course c) const
{
    if (course_id < c.course_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Course::operator>(const Course c) const
{
    if (course_id > c.course_id)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Course::operator==(const Course c) const
{
    if (course_id == c.course_id)
    {
        return true;
    }
    return false;
}

void Course::addTime(int class_id, int time)
{
    Class temp = Class(class_id, course_id, 0);
    classes->Search(&temp)->GetData()->addTime(time);
}

int Course::GetHash()
{
    return course_id;
}

void Course::addClass(int time)
{
    Class *new_class = new Class(num_of_classes, course_id, time);
    classes->Insert(new_class);
    num_of_classes++;
    delete new_class;
}

bool Course::operator!=(const Course c) const
{
    return !(c == *this);
}
