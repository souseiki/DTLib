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

using namespace std;
using namespace DTLib;


class Test:public Object
{
public:
    Test()
    {
        cout << "Test()" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }
};


int main()
{
    SmartPointer<Test> sp = new Test();
    SmartPointer<Test> spn;
    spn = sp;
    return 0;
}