/*
 * Created on Wed Nov 07 2018
 *
 * @Description: 
 * @Version: 0.1
 * @Company: Navinfo
 * @Author: Han Xin
 * @Date: Wed Nov 07 2018 0:0:19
 * @LastEditors: Han Xin
 * @LastEditTime: Wed Nov 07 2018 0:0:19
 *
 * The MIT License (MIT)
 * Copyright (c) 2018 Han Xin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "Array.h"
#include "Exception.h"

namespace DTLib
{
template < typename T>
class DynamicArray: public Array<T>
{
protected:
    int m_length;

    
    T* copy(T* array, int len, int new_len)
    {
        T* ret = new T[new_len];
        if(ret != NULL)
        {
            int size = (len < new_len) ? len : new_len;

            for(int i=0; i< size; i++)
            {
                ret[i] = array[i];
            }
        }
        return ret;
    }

    void update(T* array, int length)
    {
        if(array != NULL)
        {
            T* temp = this->m_array;
            this->m_array =  array;
            this->m_length = length;
            
            delete[] temp;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
        }
    }

    void init(T* array, int length)
    {
        if (array != NULL)
        {
            this->m_array = array;
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
        }
    }

public:
    DynamicArray(int length)
    {
        init(new T[length], length);
    }
    DynamicArray(const DynamicArray<T>& obj)
    {

        init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);

    }
    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if ( this != &obj )
        {
            update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
        }
        
        return *this;
    }

    int length() const
    {
        return this->m_length;
    }

    void resize(int length)
    {
        if(length != m_length)
        {
            update(copy(this->m_array, this->m_length, length), length);
        }
    }
    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};
}


#endif