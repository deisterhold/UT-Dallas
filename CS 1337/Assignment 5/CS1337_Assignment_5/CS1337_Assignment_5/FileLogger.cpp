//
//  FileLogger.cpp
//  CS1337_Assignment_5
//
//  Created by Daniel Eisterhold on 4/15/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "FileLogger.h"

FileLogger::FileLogger()
{
    //Open the log file
    logFile.open("Log.txt");
    if (!logFile)
    {
        cout<<"Unable to open the log file";
        exit(9);
    }
}

FileLogger::~FileLogger()
{
    //Close the log file
    logFile.close();
}

void FileLogger::displayMessage(const char *message)
{
    //Gets the current time
    time_t rawtime; //Store the unix time
    struct tm * timeinfo; //Store the time
    
    time (&rawtime); //Convert to UTC
    
    timeinfo = localtime (&rawtime); //Convert to local time
    
    char buffer[20]; //Buffer to hold time in readable form
    
    strftime (buffer, 20, "%Y-%m-%d %H:%M:%S  ", timeinfo); //Put the time into YYYY-MM-DD HH:MM:SS format
    
    //Output the time to the console and the file
    for (int letter = 0; letter < 20; letter++)
    {
        cout<<buffer[letter];
        logFile<<buffer[letter];
    }
    
    //Output the message to the console
    cout<<" "<<message<<endl;
    
    //Output the message to the file
    logFile<<" "<<message<<endl;
}