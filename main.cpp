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
#include "StaticLinkList.h"
#include "CircleList.h"

using namespace std;
using namespace DTLib;

void josephus(int n, int s, int m)
{
    CircleList<int> cl;
    for(int i=1; i<=n; i++)
    {
        cl.insert(i);
    }
    cl.move(s-1, m-1);
    while(cl.length()>0)
    {
        cl.next(); 
        cout << cl.current() << endl;
        cl.remove(cl.find(cl.current()));
    }
}

int main()
{
    josephus(41, 1, 3);
    return 0;
}