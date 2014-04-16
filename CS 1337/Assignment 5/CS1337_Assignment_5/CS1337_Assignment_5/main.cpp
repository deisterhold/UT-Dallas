//
//  main.cpp
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include <iostream>
#include "LogSingleton.h"

using namespace std;

CS1337Logger * LogSingleton::myLogger = NULL;

int main(int argc, const char * argv[])

{
    CS1337Logger *myLogger;
    myLogger = LogSingleton::GetLogger();
    myLogger->setLoggingStatus(true);
    myLogger->logMessage("Hello World!");
    myLogger->logMessage("Testing");
    myLogger->logMessage("1");
    myLogger->logMessage("2");
    myLogger->logMessage("3");
    myLogger->setLoggingStatus(false);
    myLogger->logMessage("Hello World Again!");
    myLogger->logMessage("Testing");
    myLogger->logMessage("4");
    myLogger->logMessage("5");
    myLogger->logMessage("6");
    return 0;
}

