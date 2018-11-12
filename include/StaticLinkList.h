/*
 * Created on Tue Nov 13 2018
 *
 * @Description: 
 * @Version: 0.1
 * @Contact: robotorhan@gmail.com
 * @Author: Robotor Han
 * @Date: Tue Nov 13 2018 0:11:57
 * @LastEditors: Robotor Han
 * @LastEditTime: Tue Nov 13 2018 0:11:57
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
// 1.new 函数的重载?
// 2. 应用场景？
// 3. 测试用例
#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace DTLib
{
template< typename T, int N >
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    unsigned char m_space[sizeof(Node) * N];
    int m_used[N];

    struct SNode : public Node
    {
        void* operator new(unsigned int size, void* loc)
        {
            (void)size;
            return loc;
        }
    };

    Node* create()
    {
        SNode* ret = NULL;

        for (int i=0; i<N; i++)
        {
            if( !m_used[i])
            {
                ret = reinterpret_cast<SNode*>(m_space) + i;  //疑问
                ret = new(ret)SNode(); //疑问2
                m_used[i] = 1;
                break;
            }
        }

        return ret;
    }
    void destroy(Node* pn)
    {
        SNode* space = reinterpret_cast<SNode*>(m_space);
        SNode* psn = dynamic_cast<SNode*>(pn);
        for(int i=0; i<N; i++)
        {
            if(psn == (space + i))
            {
                m_used[i] = 0;
                psn->~SNode();
            }
        }
    }

public:
    StaticLinkList()
    {
        for(int i=0; i<N; i++)
        {
            m_used[i] = 0;
        }
    }

    int capacity()
    {
        return N; 
    }

};
}


#endif