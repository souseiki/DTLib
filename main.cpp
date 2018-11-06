#include <iostream>
#include "Exception.h"
#include "SmartPointer.h"
#include "List.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"
#include "StaticArray.h"

using namespace std;
using namespace DTLib;


int main()
{
    StaticArray<int, 5> sl;
    for (int i=0; i< sl.length(); i++)
    {
        sl[i] = i + i;
    }
    for(int i=0; i< sl.length(); i++)
    {
        cout << sl[i] << endl;
    }
    StaticArray<int, 5> s2;
    s2 = sl;

    for(int i=0; i< s2.length(); i++)
    {
        cout << s2[i] << endl;
    }


    s2[6] = 100;
    return 0;
}