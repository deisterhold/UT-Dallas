//
//  CS1337Logger.cpp
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "CS1337Logger.h"

CS1337Logger::CS1337Logger()
{
    loggingEnabled = false;
}

CS1337Logger::~CS1337Logger()
{
    
}

void CS1337Logger::setLoggingStatus(bool value)
{
    loggingEnabled = value;
}

void CS1337Logger::logMessage(const char *message)
{
    if (loggingEnabled)
    {
        displayMessage(message);
    }
}

void CS1337Logger::displayMessage(const char *message)
{
    
}