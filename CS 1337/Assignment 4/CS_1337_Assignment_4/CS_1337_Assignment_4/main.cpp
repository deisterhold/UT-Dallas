//
//  main.cpp
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>

#include "Airplane.h"
#include "Helicopter.h"
#include "Rocket.h"

using namespace std;
string getInputFileName()
{
    string inputFileName; //Create String object to hold the input file location
    
    ifstream inputFile; //Create ifstream object to test if the file location is valid
    
    cout<<"Please enter a name for the input file Ex. \"Input.txt\" "<<endl;
    //Prompt the user to input the file location
    do
    {
        cin>>inputFileName; //Get the file location
        
        inputFile.open(inputFileName.c_str()); //Test opening the file at the given location
        
        if (cin.fail() || !inputFile) //If getting the file location failed or unable to open the file
        {
            cout<<"Invalid File Name. Please Try Again: "<<endl;
            //Output error message
        }
        inputFile.close(); //Close the file
    }
    while (cin.fail() || !inputFile);
    //Repeat until the file opens
    
    cout<<endl;
    //Line Space
    
    return inputFileName; //Return the valid file location
}

void stringToTokens(string stringOfTokens, vector<string *> &arrayWithTokens)
{
    //Create a char array to hold the string
    char tempArray[stringOfTokens.length()+1];
    
    //Copy the string into the char array
    stringOfTokens.copy(tempArray, stringOfTokens.length(), 0);
    
    //Append the null terminator to the end of the array (CString)
    tempArray[stringOfTokens.length()]='\0';
    
    //Create a temporary char pointer
    char * token;
    
    //Pass array to the strtok function
    token = strtok(tempArray, "\t ,");
    
    //Save each token to the string vector
    while(token != NULL)
    {
        //Output the tokens
        //cout << "Token was: " << token << endl;
        
        //Store the token in a vector
        arrayWithTokens.push_back(new string(token));
        
        //Search again for new token
        token = strtok(NULL, ", \t");
    }
}

bool validateCommand(string commandToValidate)
{
    vector<string *> arrayOfTokens;
    
    //If the command is blank skip
    if (!(commandToValidate.length() > 0)){ return false; }
    
    stringToTokens(commandToValidate, arrayOfTokens);
    
    if (arrayOfTokens.size() < 1)
    {
//        cout<<"Skipping. No command on that line."<<endl;
        return false;
    }
    
    cout<<"Validating command..."<<endl;
    
    //Determine the command
    if (*arrayOfTokens[0] == "p")
    {
        if(atoi(arrayOfTokens[1]->c_str())>= 0)
        {
            return true;
        }
    }
    else if(*arrayOfTokens[0] == "n")
    {
        //Determine what type of aircraft to create
        switch (atoi(arrayOfTokens[1]->c_str()))
        {
            case 0:
                //Validate number of pilots
                if(atoi(arrayOfTokens[2]->c_str()) >= 0 && atoi(arrayOfTokens[2]->c_str()) < 256)
                {
                    //Validate number of pasengers
                    if(atoi(arrayOfTokens[3]->c_str()) >= 0 && atoi(arrayOfTokens[3]->c_str()) < 65536)
                    {
                        //Validate if payload is valid
                        if(atoi(arrayOfTokens[4]->c_str()) > 0 && atoi(arrayOfTokens[4]->c_str()) < 2147483647)
                        {
                            return true;
                        }
                    }
                }
                break;
            case 1:
                //Create an airplane aircraft
                //Validate wing width is within range
                if(atoi(arrayOfTokens[2]->c_str()) > 0 && atoi(arrayOfTokens[2]->c_str()) < 65536)
                {
                    //Validate propeller diameter is within range
                    if(atoi(arrayOfTokens[3]->c_str())> 0 && atoi(arrayOfTokens[3]->c_str()) < 256)
                    {
                        //Validate if is a jet
                        if(*arrayOfTokens[4] == "true" || *arrayOfTokens[4] == "false")
                        {
                            return true;
                        }
                    }
                }
                break;
            case 2:
                //Create a helicopter aircraft
                //Validate number of blades is within range
                if(atoi(arrayOfTokens[2]->c_str()) > 0 && atoi(arrayOfTokens[2]->c_str()) < 256)
                {
                    //Validate number of rotors is in range
                    if(atoi(arrayOfTokens[3]->c_str())> 0 && atoi(arrayOfTokens[3]->c_str()) < 256)
                    {
                        return true;
                    }
                }
                break;
            case 3:
                //Create a rocket aircraft
                //Validate the height
                if(atoi(arrayOfTokens[2]->c_str()) > 0 && atoi(arrayOfTokens[2]->c_str()) < 2147483647)
                {
                    //Validate the number of fins
                    if(atoi(arrayOfTokens[3]->c_str())> 0 && atoi(arrayOfTokens[3]->c_str()) < 256)
                    {
                        return true;
                    }
                }
                break;
            default:
                return false;
                break;
        }
    }
    
    return false;
}

string readLine(ifstream &myFile)
{
    string command = "";
    string tempString = "";
    getline(myFile, tempString);
    
    //Loop through the entire line that was read
    for (int length = 0; length < tempString.length(); length++)
    {
        //If there is a forward slash
        if (tempString[length] == '/')
        {
            //add the string to the other string up until the forward slash
            for (int counter = 0; counter < length; counter++)
            {
                command += tempString[counter];
            }
            //Break out of the loop
            break;
        }
    }
    
    //Make sure the command is valid
    if(validateCommand(command))
    {
        return command;
    }
    
//    cout<<"Command could not be understood"<<endl;
    
    //If not valid then return a blank string
    return "";
}

void processCommand(string commandToProcess, vector<Aircraft *> &arrayOfAircraft)
{
    //Vector to hold the tokens
    vector<string *> arrayOfTokens;
    
    //Convert string into tokens
    stringToTokens(commandToProcess, arrayOfTokens);
    
    //If the command is blank skip
    if (commandToProcess.length() == 0){ return; }
    
    cout<<"Processing command..."<<endl;
    
    //Determine the command
    if (*arrayOfTokens[0] == "n")
    {
        if (*arrayOfTokens[1] == "0")
        {
            cout<<"Creating new Aircraft..."<<endl;
            
            //Create the aircraft with the read in parameters
            Aircraft *myAircraft = new Aircraft(atoi(arrayOfTokens[2]->c_str()),atoi(arrayOfTokens[3]->c_str()),atoi(arrayOfTokens[4]->c_str()));
            
            //Add the object to the array
            arrayOfAircraft.push_back(myAircraft);
        }
        else if (*arrayOfTokens[1] == "1")
        {
            cout<<"Creating new Airplane..."<<endl;
            
            //Create airplane pointer
            Airplane *myAirplane;
            
            if(*arrayOfTokens[4] == "true")
            {
                //Initialize the airplane object with the read in parameters
                myAirplane = new Airplane(atoi(arrayOfTokens[2]->c_str()),atoi(arrayOfTokens[3]->c_str()), true);
                
                //Add the object to the array
                arrayOfAircraft.push_back(myAirplane);
            }
            else if(*arrayOfTokens[4] == "false")
            {
                //Initialize the airplane object with the read in parameters
                myAirplane = new Airplane(atoi(arrayOfTokens[2]->c_str()),atoi(arrayOfTokens[3]->c_str()), false);
                
                //Add the object to the array
                arrayOfAircraft.push_back(myAirplane);
            }
        }
        else if (*arrayOfTokens[1] == "2")
        {
            cout<<"Creating new Helicopter..."<<endl;
            
            //Create the helicopter object with the read in parameters
            Helicopter *myHelicopter = new Helicopter(atoi(arrayOfTokens[2]->c_str()),atoi(arrayOfTokens[3]->c_str()));
            
            //Add the object to the array
            arrayOfAircraft.push_back(myHelicopter);
        }
        else if (*arrayOfTokens[1] == "3")
        {
            cout<<"Creating new Rocket..."<<endl;
            
            //Create the rocket object with the read in parameters
            Rocket *myRocket = new Rocket(atoi(arrayOfTokens[2]->c_str()),atoi(arrayOfTokens[3]->c_str()));
            
            //Add the object to the array
            arrayOfAircraft.push_back(myRocket);
        }
        
    }
    else if(*arrayOfTokens[0] == "p")
    {
        if (*arrayOfTokens[1] == "0")
        {
            cout<<"Printing All Aircraft Characteristics..."<<endl;
            for (int aircraftNumber = 0; aircraftNumber < arrayOfAircraft.size(); aircraftNumber++)
            {
                cout<<"Printing Aircraft #"<<aircraftNumber+1<<" Characteristics..."<<endl;
                arrayOfAircraft[aircraftNumber]->printCharacteristics();
            }
        }
        else
        {
            if(atoi(arrayOfTokens[1]->c_str())-1 < arrayOfAircraft.size())
            {
                cout<<"Printing Aircraft #"<<atoi(arrayOfTokens[1]->c_str())<<" Characteristics..."<<endl;
                arrayOfAircraft[atoi(arrayOfTokens[1]->c_str())-1]->printCharacteristics();
            }
            else
            {
                cout<<"That aircraft does not exist. "<<endl;
            }
        }
    }
}

void readFile(ifstream &fileToRead, vector<Aircraft *> &aircraftArray)
{
    cout<<"Reading File..."<<endl;
    while (!fileToRead.eof())
    {
        processCommand(readLine(fileToRead), aircraftArray);
    }
    cout<<"Done Reading File."<<endl;
}

int main(int argc, const char * argv[])
{
    vector<Aircraft *> hangerOfAircraft;
    
    ifstream inputFile;
    inputFile.open(getInputFileName().c_str());
    
    //Reads the input file then processes the commands
    readFile(inputFile, hangerOfAircraft);
    
    return 0;
}

