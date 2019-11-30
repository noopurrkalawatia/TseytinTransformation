//============================================================================
// Name        : tseytinTransform.cpp
// Author      : Noopur R K
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "tseytinUtil.h"
using namespace std;

#define MAX_SIZE_ARGUMENTS 2

int main(int argc, char *argv[])
{
    if(argc < MAX_SIZE_ARGUMENTS || argc > MAX_SIZE_ARGUMENTS)
    {
        cout << "Invalid number of arguments" << endl;
        cout << "Usage is ./tseytinTransform <>.bench " << endl;
        return 0;
    }

    string inputFileName = argv[1];

    tseytinUtil tseytinOb;
    tseytinOb.performTseytinTransformation(inputFileName);

	return 0;
}
