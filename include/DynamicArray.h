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
public:
    DynamicArray(int length)
    {
        this->m_array = new T[length];
        if (this->m_array != NULL)
        {
            this->m_length = length;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
        }
    }
    DynamicArray(const DynamicArray<T>& obj)
    {
        this->m_array = new T[obj.m_length];
        if (this->m_array ！= NULL)
        {
            this->m_length = obj.m_length;
            for(int i=0; i< obj.m_length; i++)
            {
                this->m_array[i] = obj.m_array[i];
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
        }
    }
    DynamicArray<T>& operator= (const DynamicArray<T>& obj)
    {
        if ( this != &obj )
        {
            T* array = new T[obj.m_length];
            if (array != NULL)
            {
                for (int i=0; i<obj.m_length; i++)
                {
                    array[i] = obj.m_array[i];
                }
                T* temp = this->m_array;
                this->m_array = array;
                this->m_length = obj.m_length;

                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
            }
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
            T* array = new T[length];
            if (array != NULL)
            {
                int size = (length < m_length) ? length : m_length;
                for(int i=0; i<size; i++)
                {
                    array[i] = this->m_array[i];
                }
                T* temp  = this->m_array;
                this->m_array = array;
                this->m_length = length;
                
                delete[] temp;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create DynamicArray object...");
            }
        }
    }
    ~DynamicArray()
    {
        delete[] this->m_array;
    }
};
}


#endif