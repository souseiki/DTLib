#ifndef OBJECT_H
#define OBJECT_H

#include<iostream>

namespace DTLib
{
class Object
{
public:

    void* operator new(size_t size) throw();
    void operator delete(void* p);

    void* operator new[] (size_t  size) throw();
    void operator delete[] (void* p);
    virtual ~Object() = 0;
};

}


#endif