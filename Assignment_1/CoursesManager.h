#ifndef WET1_COURSESMANAGER_H
#define WET1_COURSESMANAGER_H

#include <iostream>
#include "AVLtree.h"
#include "Class.h"
#include "Course.h"
#include "Exceptions.h"

class CoursesManager
{
private:
    AVLtree<Course> courseTree;
    AVLtree<Class> timeTree;
    int totalClasses;
    int watchedClasses;
public:
    CoursesManager() = default; //c'tor
    ~CoursesManager() = default;
    CoursesManager* Init();
    void addCourse(int courseID, int numOfClasses);
    void removeCourse(int CourseID);
    void watchClass(int courseID, int classID, int time);
    void timeViewed(int courseID, int classID, int* timeviewed);
    void getMostViewedClasses(int numOfClasses, int* courses, int* classes);
};
#endif
