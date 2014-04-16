//
//  CS1337Logger.h
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS1337_Assignment_5__CS1337Logger__
#define __CS1337_Assignment_5__CS1337Logger__

#include <iostream>
#include <time.h>

using namespace std;

class CS1337Logger
{
public:
    CS1337Logger();
    ~CS1337Logger();
    
    void setLoggingStatus(bool);
    void logMessage(const char *);
    
    virtual void displayMessage(const char *);
private:
    bool loggingEnabled;
};

#endif /* defined(__CS1337_Assignment_5__CS1337Logger__) */
