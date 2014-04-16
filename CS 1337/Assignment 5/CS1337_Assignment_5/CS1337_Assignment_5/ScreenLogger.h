//
//  ScreenLogger.h
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS1337_Assignment_5__ScreenLogger__
#define __CS1337_Assignment_5__ScreenLogger__

#include <iostream>
#include "CS1337Logger.h"
using namespace std;

class ScreenLogger : public CS1337Logger
{
public:
    void displayMessage(const char *);
};

#endif /* defined(__CS1337_Assignment_5__ScreenLogger__) */
