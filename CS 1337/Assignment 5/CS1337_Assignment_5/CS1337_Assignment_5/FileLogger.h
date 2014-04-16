//
//  FileLogger.h
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS1337_Assignment_5__FileLogger__
#define __CS1337_Assignment_5__FileLogger__

#include <iostream>
#include <fstream>
#include "CS1337Logger.h"

using namespace std;

class FileLogger : public CS1337Logger
{
public:
    FileLogger();
    ~FileLogger();
    void displayMessage(const char *);
private:
    ofstream logFile;
};

#endif /* defined(__CS1337_Assignment_5__FileLogger__) */
