#include "library.h"
#include "CoursesManager.h"

void* Init()
{
    try {
        CoursesManager* DS = new CoursesManager();
        return (void*)DS;
    }
    catch (const std::bad_alloc& e)
    {
        return nullptr;
    }
    catch (const Exception& e)
    {
        return nullptr;
    }
}

StatusType AddCourse(void* DS, int courseID, int numOfClasses)
{
    if (DS == nullptr) {
        return INVALID_INPUT;
    }
    try {
        auto targetManager = (CoursesManager*)DS;
        targetManager->addCourse(courseID, numOfClasses);
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs& e) {
        return INVALID_INPUT;
    }
    catch (const TreeValueExists& e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCourse(void* DS, int courseID)
{
    if (DS == nullptr) {
        return INVALID_INPUT;
    }
    try {
        auto targetManager = (CoursesManager*)DS;
        targetManager->removeCourse(courseID);
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs& e) {
        return INVALID_INPUT;
    }
    catch (const TreeValueNoExist& e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType WatchClass(void* DS, int courseID, int classID, int time)
{
    if (DS == nullptr) {
        return INVALID_INPUT;
    }
    try {
        auto targetManager = (CoursesManager*)DS;
        targetManager->watchClass(courseID, classID, time);
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs& e) {
        return INVALID_INPUT;
    }
    catch (const TreeValueNoExist& e) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType TimeViewed(void* DS, int courseID, int classID, int* timeViewed)
{
    if (DS == nullptr) {
        return INVALID_INPUT;
    }
    try {
        auto targetManager = (CoursesManager*)DS;
        targetManager->timeViewed(courseID, classID, timeViewed);
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs& e)
    {
        return INVALID_INPUT;
    }
    catch (const TreeValueNoExist& e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetMostViewedClasses(void* DS, int numOfClasses, int* courses, int* classes)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager*)DS;
        targetManager->getMostViewedClasses(numOfClasses, courses, classes);
    }
    catch (const std::bad_alloc& e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs& e)
    {
        return INVALID_INPUT;
    }
    catch (const TooManyClasses& e)
    {
        return FAILURE;
    }
    //todo: do we need to put a catch for treeValueNotFound
    return SUCCESS;
}
void Quit(void** DS)
{
    auto deleteManager = (CoursesManager*)(*DS);
    delete deleteManager;
    *DS = nullptr;
}