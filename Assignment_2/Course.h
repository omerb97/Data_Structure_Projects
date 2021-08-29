#include "Class.h"
#include "HashTable.h"

#ifndef COURSE_H
#define COURSE_H

class Course
{
private:
    int course_id;
    int num_of_classes;
    HashTable<Class> *classes;

public:
    Course() = default;

    Course(const Course &course);

    Course(int course_id);

    Course &operator=(Course &other);

    ~Course();

    int getCourseId();

    int getNumOfClasses();

    Class *getClass(int id);

    void addClass(int time = 0);

    void addTime(int class_id, int time);

    bool operator<(const Course c) const;

    bool operator>(const Course c) const;

    bool operator==(const Course c) const;

    bool operator!=(const Course c) const;

    int GetHash();

};

#endif
