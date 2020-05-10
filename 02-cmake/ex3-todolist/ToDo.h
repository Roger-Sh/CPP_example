/*************************************************************************
	> File Name: ToDo.h
	> Author: 
	> Mail: 
	> Created Time: Di 18 Feb 2020 15:47:37 CET
 ************************************************************************/

#ifndef _TODO_H
#define _TODO_H

#include <string>
#include <vector>

class ToDo
{
public:
    ToDo();     //constructor
    ~ToDo();    //deconstructor

    size_t size() const;

    void addTask(const std::string& task);
    std::string getTask(size_t index) const;

private:
    std::vector<std::string> this_tasks;
};

#endif // _TODO_H
