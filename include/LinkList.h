/*
 * Created on Sat Nov 10 2018
 *
 * @Description: 
 * @Version: 0.1
 * @Contact: robotorhan@gmail.com
 * @Author: Robotor Han
 * @Date: Sat Nov 10 2018 16:24:56
 * @LastEditors: Robotor Han
 * @LastEditTime: Sat Nov 10 2018 16:24:56
 *
 * The MIT License (MIT)
 * Copyright (c) 2018 Robotor Han
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


// TODO:
// 理解删除等操作指针偏移的原理
//理解头结点的作用，如果没有需要怎样改？


#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "List.h"
#include "Exception.h"
namespace DTLib
{
template <typename T>
class LinksList: public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct: public Object
    {
        char reserved[sizeof(T)];
        Node* next;
    } m_header;
    int  m_length;

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }
        return ret;
    }

public:
    LinksList()
    {
        m_header.next = NULL;
        m_length = 0;
    }

    bool insert(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        if( ret )
        {
            Node* node = new Node();
            if (node != NULL)
            {
                Node* current = position(i); 
                node->value = e;
                node->next = current->next;
                current->next = node;
                m_length ++;
            }
            else
            {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element ...");
            }
        }
        return ret;
    }

    bool remove(int i)
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if( ret )
        {
            Node* current = position(i); 
            Node* to_del = current->next;
            current->next = to_del->next;
            delete to_del;
            m_length --;
        }
        return ret;
    }

    bool set(int i, const T& e)
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if( ret )
        {
            position(i)->next->value = e;
        }
        return ret;      
    }

    T get(int i) const
    {
        T ret; 
        if(get(i, ret))
        {
            return ret;
        }
        else
        {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element...");
        }
        return ret;
    }

    bool get(int i, T& e) const
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if( ret )
        {            
            e = position(i)->next->value;
        }
        return ret;  
    }

    int length() const
    {
        return m_length;
    }

    void clear()
    {
        while(m_header.next)
        {
            Node* to_del = m_header.next;
            m_header.next = to_del->next;
            delete to_del;
        }
        m_length = 0;
    }

    ~LinksList()
    {
        clear();
    }

};
}
#endif