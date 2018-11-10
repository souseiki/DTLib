#include <iostream>
#include "Exception.h"
#include "SmartPointer.h"
#include "List.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"
#include "DynamicArray.h"
#include "LinkList.h"

using namespace std;
using namespace DTLib;


int main()
{
    LinksList<int> lst;
    for(int i=0; i< 5; i++)
    {
        lst.insert(0, i);
        lst.set(0, i*i);
    }

    for(int i=0; i<lst.length(); i++)
    {
        int a = - 1;
        lst.get(i, a);
        std::cout << a << std::endl;
    }

    lst.remove(2);
    for(int i=0; i<lst.length(); i++)
    {
        std::cout << lst.get(i) << std::endl;
    }

    return 0;
}