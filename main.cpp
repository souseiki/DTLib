#include <iostream>
#include "Exception.h"
#include "SmartPointer.h"
#include "List.h"
#include "SeqList.h"
#include "StaticList.h"
#include "DynamicList.h"

using namespace std;
using namespace DTLib;


int main()
{
    DynamicList<int> l(5);

    for (int i=0; i<l.capacity(); i++)
    {
        l.insert(0,i);
    }

    
    for (int i=0; i<l.length(); i++)
    {
        std::cout << l[i] << std::endl;
    }

    l[0] *= l[0];
    for (int i=0; i<l.length(); i++)
    {
        std::cout << l[i] << std::endl;
    }
    // try
    // {
    //     l[5] = 5;
    // }
    // catch (const Exception& e)
    // {
    //     cout << e.message() << endl;
    //     cout << e.location() << endl;
    // }

    return 0;
}