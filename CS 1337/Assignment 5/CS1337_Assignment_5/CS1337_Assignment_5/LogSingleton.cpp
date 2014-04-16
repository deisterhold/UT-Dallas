//
//  LogSingleton.cpp
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "LogSingleton.h"

CS1337Logger * LogSingleton::GetLogger()
{
    if (myLogger == NULL)
    {
        const bool logToFile = true;
        if (logToFile)
        {
            //Log to the console and a file
            myLogger = new FileLogger;
        }
        else
        {
            //Log to the console
            myLogger = new ScreenLogger;
        }
    }
    
    return myLogger;
}
