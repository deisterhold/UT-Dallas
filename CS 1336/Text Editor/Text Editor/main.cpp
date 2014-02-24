//  Text Editor
//
//  Type some text and saves to a selected directory
//  Created by Daniel Eisterhold on 10/2/13.
//  Copyright (c) 2013 Daniel Eisterhold. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;

string username;
string directory;
int operatingSystem;

#include "main.h"

int main()
{
    //Get the operating system so you know the correct type of
    //file system
    do
    {
        cout<<"Operating System \n"<<setfill('-')<<setw(40)<<"-"<<endl;
        cout<<"1. Windows 7/8"<<endl;
        cout<<"2. OS X 10.7-10.9"<<endl;
        cout<<"Please choose your operating system: ";
        cin>>operatingSystem;
        if (operatingSystem != 1 && operatingSystem != 2) {
            cout<<"Invalid Value."<<endl;
        }
    } while (operatingSystem != 1 && operatingSystem != 2);
    
    //Set the file system depending on the operating system
    switch (operatingSystem) {
        //Sets the directory for Windows 7/8
        case 1:
            directory = "C:\\Users\\";
            break;
        //Sets the directory for OS X 10.7-10.9
        case 2:
            directory = "/Users/";
            break;
        //Default directory is for Windows
        default:
            directory = "C:\\Users\\";
            break;
    }
    
    //Ask the user for their username
    cout<<"Please enter your username (Ex: JohnSmith): ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin,username);
    
    //Creates the directory with the correct file system
    //and the correct username
    directory = directory + username + "/";
    
    //Loop through the menu until user chooses to quit
    for (int x = 0; x != -1; x++) {
        //The task that the user wishes to do
        int task;
        
        //Asks user what they wish to do
        //If input is invalid it repeats
        do {
            cout<<"\nText Editor\n"<<"--------------------------"<<endl;
            cout<<"1. Create New Document"<<endl;
            cout<<"2. Open Existing Document"<<endl;
            cout<<"3. Quit Program"<<endl;
            cout<<"\nWhat would you like to do? ";
            cin>>task;
            cin.clear();
            cin.ignore(1000, '\n');
        } while (task != 1 && task != 2 && task != 3);
        
        //Does the task based upon user selection
        switch (task) {
            //Creates a file then opens for editing
            case 1:
                writeToFile(createFile());
                break;
            //Opens a file then allows for editing
            case 2:
                writeToFile(openFile());
                break;
            case 3:
                exit(0);
                break;
            //Create a new document if something messed up
            default:
                createFile();
                break;
        }
    }

    
    return 0;
}