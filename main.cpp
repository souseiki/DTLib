#include <iostream>
#include "Exception.h"
#include "SmartPointer.h"

using namespace std;
using namespace DTLib;


int main()
{
    InvalidOperationException* e = new InvalidOperationException();

    delete e;
    return 0;
}