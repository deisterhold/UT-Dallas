//
//  LogSingleton.h
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS1337_Assignment_5__LogSingleton__
#define __CS1337_Assignment_5__LogSingleton__

#include <iostream>
#include "ScreenLogger.h"
#include "FileLogger.h"

using namespace std;

class LogSingleton : public ScreenLogger, FileLogger
{
public:
    static CS1337Logger * GetLogger();
private:
    static CS1337Logger *myLogger;
};

#endif /* defined(__CS1337_Assignment_5__LogSingleton__) */
