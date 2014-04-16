//
//  ScreenLogger.cpp
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "ScreenLogger.h"

void ScreenLogger::displayMessage(const char *message)
{
    //Gets the current time
    time_t rawtime; //Store the unix time
    struct tm * timeinfo; //Store the time
    
    time (&rawtime); //Convert to UTC
    
    timeinfo = localtime (&rawtime); //Convert to local time
    
    char buffer[20]; //Buffer to hold time in readable form
    
    strftime (buffer, 20, "%Y-%m-%d %H:%M:%S  ", timeinfo); //Put the time into YYYY-MM-DD HH:MM:SS format
    
    //Output the time to the console
    for (int letter = 0; letter < 20; letter++)
    {
        cout<<buffer[letter];
    }
    
    //Output the message to the console
    cout<<" "<<message<<endl;
}