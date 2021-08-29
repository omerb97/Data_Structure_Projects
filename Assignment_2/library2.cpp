#include "library2.h"
#include "CoursesManager.h"

void *Init()
{
    try
    {
        CoursesManager *DS = new CoursesManager();
        return (void *) DS;
    }
    catch (const std::bad_alloc &e)
    {
        return nullptr;
    }
    catch (const Exception &e)
    {
        return nullptr;
    }
}

StatusType AddCourse(void *DS, int courseID)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager *) DS;
        targetManager->addCourse(courseID);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs &e)
    {
        return INVALID_INPUT;
    }
    catch (const ValueExists &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType RemoveCourse(void *DS, int courseID)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager *) DS;
        targetManager->removeCourse(courseID);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs &e)
    {
        return INVALID_INPUT;
    }
    catch (const ValueNoExist &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType AddClass(void *DS, int courseID, int *classID)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager *) DS;
        targetManager->addClass(courseID, classID);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs &e)
    {
        return INVALID_INPUT;
    }
    catch (const ValueNoExist &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType WatchClass(void *DS, int courseID, int classID, int time)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager *) DS;
        targetManager->watchClass(courseID, classID, time);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs &e)
    {
        return INVALID_INPUT;
    }
    catch (const ValueNoExist &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType TimeViewed(void *DS, int courseID, int classID, int *timeViewed)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager *) DS;
        targetManager->timeViewed(courseID, classID, timeViewed);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs &e)
    {
        return INVALID_INPUT;
    }
    catch (const ValueNoExist &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType GetIthWatchedClass(void *DS, int i, int *courseID, int *classID)
{
    if (DS == nullptr)
    {
        return INVALID_INPUT;
    }
    try
    {
        auto targetManager = (CoursesManager *) DS;
        targetManager->getIthWatchedClass(i, courseID, classID);
    }
    catch (const std::bad_alloc &e)
    {
        return ALLOCATION_ERROR;
    }
    catch (const InvalidInputs &e)
    {
        return INVALID_INPUT;
    }
    catch (const TooManyClasses &e)
    {
        return FAILURE;
    }
    return SUCCESS;
}

void Quit(void **DS)
{
    auto deleteManager = (CoursesManager *) (*DS);
    delete deleteManager;
    *DS = nullptr;
}