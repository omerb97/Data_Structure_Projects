#ifndef COURSESMANAGER_H
#define COURSESMANAGER_H

#include <iostream>
#include "HashTable.h"
#include "AVLRankTree.h"
#include "Class.h"
#include "Course.h"
#include "Exceptions.h"

class CoursesManager
{
private:
    HashTable<Course> courses;
    AVLRankTree<Class> timeTree;
    int totalClasses;
    int watchedClasses;
public:
    CoursesManager() = default; //c'tor
    ~CoursesManager() = default;

    void addCourse(int courseID);

    void removeCourse(int courseID);

    void addClass(int courseID, int *classID);

    void watchClass(int courseID, int classID, int time);

    void timeViewed(int courseID, int classID, int *timeviewed);

    void getIthWatchedClass(int i, int *courseID, int *classID);
};

#endif
