#ifndef POINTER_H
#define POINTER_H

namespace DTLib
{
template<typename T>
class Pointer: public Object
{
protected:
    T* m_pointer;

public:
    Pointer(T* p=NULL)
    {
        m_pointer = p;
    }
    T* operator->()
    {
        return m_pointer;
    }
    T& operator*()
    {
        return *m_pointer;
    }
    bool isNull()
    {
        return (m_pointer == NULL);
    }
    T* get()
    {
        return m_pointer;
    }
};
}

#endif