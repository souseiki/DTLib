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

#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "List.h"
#include "Exception.h"
namespace DTLib
{
template <typename T>
class LinkList: public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node* next;
    };

    mutable struct: public Object
    {
        char reserved[sizeof(T)];  //char占一个字节，所以用char来创建预留空间
        Node* next;
    } m_header;

    int  m_length;
    int m_step;
    Node* m_current;

    Node* position(int i) const
    {
        Node* ret = reinterpret_cast<Node*>(&m_header);
        for(int p=0; p<i; p++)
        {
            ret = ret->next;
        }
        return ret;
    }

    virtual Node* create()
    {
        return new Node();
    }
    virtual void destroy(Node* pn)
    {
        delete pn;
    }


public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }

    bool insert(int i, const T& e)
    {
        bool ret = ((i >= 0) && (i <= m_length));
        if( ret )
        {
            Node* node = create();
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
         
            if(m_current == to_del)
            {
                m_current = to_del->next;
            }
            current->next = to_del->next;
            m_length --;
            destroy(to_del);
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


    int find(const T& e) const
    {
        int ret = -1;
        int i = 0;
        Node* node = m_header.next;
        while(node)
        {
            if (node->value == e)
            {
                ret = i;
                break;
            }
            else
            {
                i++;
                node = node->next;
            }
        }
        return ret;
    }


    bool move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i <= m_length) && (step > 0);
        if (ret)
        {
            m_current = position(i)->next;
            m_step = step;
        }
        return ret;
    }

    bool end()
    {
        return (m_current == NULL);
    }


    T current()
    {
        if(!end())
        {
            return m_current->value;
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position...");
        }
    }

    bool next()
    {
        int i=0;
        while( (i < m_step) && !end() )
        {
            m_current = m_current->next;
            i ++;
        }
        return (i == m_step);
    }

    void clear()
    {
        while(m_header.next)
        {
            Node* to_del = m_header.next;
            m_header.next = to_del->next;
            m_length --;
            destroy(to_del);
        }
        
    }

    ~LinkList()
    {
        clear();
    }

};
}
#endif