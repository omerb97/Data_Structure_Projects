#include "CoursesManager.h"


//CoursesManager::~CoursesManager() {
//    //todo: is this the correct way to do it or should we do it some default way
//    auto *deleteTime = &(this->timeTree);
//    delete deleteTime;
//    auto *deleteCourses = &(this->courseTree);
//    delete deleteCourses;
//}

void CoursesManager::addCourse(int courseID, int numOfClasses)
{
    if (courseID <= 0 || numOfClasses <= 0)
    {
        throw InvalidInputs();
    }
    Course newCourse(courseID, numOfClasses);
    if (this->courseTree.search(newCourse) != nullptr)
    {
        throw TreeValueExists();
    }
    //will only reach here if everything worked
    this->courseTree.insert(newCourse);
    totalClasses += numOfClasses;
}

void CoursesManager::removeCourse(int CourseID)
{
    if (CourseID <= 0)
    {
        throw InvalidInputs();
    }

    Course searchCourse(CourseID, 1);
    if (this->courseTree.search(searchCourse) == nullptr)
    {
        throw TreeValueNoExist();
    }
    auto wantedCourse = this->courseTree.search(searchCourse)->data;
    int numOfClasses = wantedCourse.getNumOfClasses();
    for (int i = 0; i < numOfClasses; i++)
    {
        if (timeTree.search(wantedCourse.getClass(i)) != nullptr)
        {
            watchedClasses--;
            this->timeTree.deleteNode(wantedCourse.getClass(i));
        }
    }
    totalClasses = totalClasses - wantedCourse.getNumOfClasses();
    this->courseTree.deleteNode(wantedCourse); //todo: does this free the data inside?


}

void CoursesManager::watchClass(int courseID, int classID, int time)
{
    if (courseID <= 0 || classID < 0 || time <= 0) {
        throw InvalidInputs();
    }
    Course searchCourse(courseID, 1);
    Course* wantedCourse = (&((this->courseTree.search(searchCourse))->data));

    if (wantedCourse == nullptr) {
        throw TreeValueNoExist();
    }
    if ((classID + 1) > wantedCourse->getNumOfClasses()) {
        throw InvalidInputs();
    }

    Class wantedClass = wantedCourse->getClass(classID);
    //todo: the function wnated class returns by value? so maybe if we change some value here it wont change it?
    if (wantedClass.getTime() != 0) {
        this->timeTree.deleteNode(wantedClass);
        wantedClass.addTime(time);
        this->timeTree.insert(wantedClass);
    }
    if (wantedClass.getTime() == 0) {
        wantedClass.addTime(time);
        watchedClasses++;
        this->timeTree.insert(wantedClass);
    }
    wantedCourse->addTime(classID, time);
}

void CoursesManager::timeViewed(int courseID, int classID, int* timeviewed)
{
    if (courseID <= 0 || classID < 0) {
        throw InvalidInputs();
    }

    Course searchCourse(courseID, 1);
    Node<Course>* isExistCourse = (this->courseTree.search(searchCourse));
    if (isExistCourse == nullptr)
    {
        throw TreeValueNoExist();
    }
    Course wantedCourse = this->courseTree.search(searchCourse)->data;

    if ((classID + 1) > wantedCourse.getNumOfClasses())
    {
        throw InvalidInputs();
    }

    Class wantedClass = wantedCourse.getClass(classID);
    *timeviewed = wantedClass.getTime();

}

void CoursesManager::getMostViewedClasses(int numOfClasses, int* courses, int* classes)
{
    if (numOfClasses <= 0)
    {
        throw InvalidInputs();
    }
    if (numOfClasses > totalClasses)
    {
        throw TooManyClasses();
    }

    int index = 0;

    Class* mostViewed = new Class[numOfClasses];
    if (timeTree.getMax())
    {
        timeTree.searchByMax(timeTree.getMax(), mostViewed, numOfClasses, &index);
    }
    if (numOfClasses > watchedClasses)
    {
        searchByMin(courseTree.getMin(), mostViewed, numOfClasses, &index);
    }
    for (int i = 0; i < numOfClasses; i++)
    {
        courses[i] = mostViewed[i].getCourseId();
        classes[i] = mostViewed[i].getClassId();
    }
    delete[] mostViewed;
}


