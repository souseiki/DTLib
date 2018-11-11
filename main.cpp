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
    }

    for(lst.move(0); !lst.end(); lst.next())
    {
        cout << lst.current() << endl;
    }


    return 0;
}