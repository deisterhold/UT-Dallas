
//
//  LoanManager.cpp
//  CS_1337_Assignment_3
//
//  Created by Daniel Eisterhold on 3/19/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "LoanManager.h"

//Constructor and Destructor
LoanManager::LoanManager()
{
    
    //Prompt for the input file location
    inputFileName = getInputFileName();
    
    //Open the input file
    ifstream inputFile;
    inputFile.open(inputFileName.c_str());
    
    if(!inputFile) //Make sure the files opened correctly
    {
        if(!inputFile)cout<<"Error opening the input file"<<endl;
        exit(1);
    }
    
    //Start the program
    this->readFile(inputFile);
}

//Public methods and variables
void LoanManager::readFile(ifstream &fileToRead)
{
    cout<<"Reading File..."<<endl;
    while (!fileToRead.eof())
    {
        processCommand(readLine(fileToRead));
    }
    cout<<"Done Reading File."<<endl;
}

//Private methods and variables
bool LoanManager::validateCommand(string commandToValidate)
{
    vector<string *> arrayOfTokens;
    
    stringToTokens(commandToValidate, arrayOfTokens);
    
    //Check if the there exists a command in the string
    if (commandToValidate.length() > 0)
    {
        //Determine the command
        if (*arrayOfTokens[0] == "cp")
        {
            if(atof(arrayOfTokens[1]->c_str())> 0)
            {
                return true;
            }
        }
        else if(*arrayOfTokens[0] == "n")
        {
            if(atof(arrayOfTokens[1]->c_str())> 0)
            {
                if(atof(arrayOfTokens[2]->c_str())> 0)
                {
                    if(atof(arrayOfTokens[3]->c_str())> 0)
                    {
                        return true;
                    }
                }
            }
        }
        else if(*arrayOfTokens[0] == "mi")
        {
            if(atof(arrayOfTokens[1]->c_str())> 0)
            {
                if(atof(arrayOfTokens[2]->c_str())> 0)
                {
                    return true;
                }
            }
        }
        else if(*arrayOfTokens[0] == "mp")
        {
            if(atof(arrayOfTokens[1]->c_str())> 0)
            {
                if(atof(arrayOfTokens[2]->c_str())> 0)
                {
                    return true;
                }
            }
        }
        else if(*arrayOfTokens[0] == "pf")
        {
            if(atof(arrayOfTokens[1]->c_str())> 0)
            {
                return true;
            }
        }
        else if(*arrayOfTokens[0] == "rp")
        {
            if(atof(arrayOfTokens[1]->c_str())> 0)
            {
                if(atof(arrayOfTokens[2]->c_str())> 0)
                {
                    return true;
                }
            }
        }
        else if(*arrayOfTokens[0] == "sh")
        {
            if (atoi(arrayOfTokens[1]->c_str()) > 0)
            {
                return true;
            }
        }
    }
    return false;
}

void LoanManager::processCommand(string commandToProcess)
{
    //Vector to hold the tokens in the command
    vector<string *> arrayOfTokens;
    
    //Convert string to tokens
    stringToTokens(commandToProcess, arrayOfTokens);
    
    //Determine the command
    if (*arrayOfTokens[0] == "cp")
    {
        cout<<"Calculating payoff..."<<endl;
        myLoans[atoi(arrayOfTokens[1]->c_str())-1].calculatePayoff();
    }
    else if(*arrayOfTokens[0] == "n")
    {
        cout<<"Creating new loan..."<<endl;
        createNewLoan(atof(arrayOfTokens[1]->c_str()), atof(arrayOfTokens[2]->c_str()), atof(arrayOfTokens[3]->c_str()));
    }
    else if(*arrayOfTokens[0] == "mi")
    {
        cout<<"Modifying interest rate..."<<endl;
        myLoans[atoi(arrayOfTokens[1]->c_str())-1].setInterest(atof(arrayOfTokens[2]->c_str()));
    }
    else if(*arrayOfTokens[0] == "mp")
    {
        cout<<"Modifying payment..."<<endl;
        myLoans[atoi(arrayOfTokens[1]->c_str())-1].setPayment(atof(arrayOfTokens[2]->c_str()));
    }
    else if(*arrayOfTokens[0] == "pf")
    {
        cout<<"Printing amortization table..."<<endl;
        myLoans[atoi(arrayOfTokens[1]->c_str())-1].printAmortizationTable();
    }
    else if(*arrayOfTokens[0] == "rp")
    {
        cout<<"Payment received..."<<endl;
        myLoans[atoi(arrayOfTokens[1]->c_str())-1].makePayment(atof(arrayOfTokens[2]->c_str()));
    }
    else if(*arrayOfTokens[0] == "sh")
    {
        cout<<"Showing history of loan..."<<endl;
        myLoans[atoi(arrayOfTokens[1]->c_str())-1].showHistory();
    }
}

void LoanManager::createNewLoan(double principal, double interestRate, double monthlyPayment)
{
    //Increase the counter to keep track of the number of loans
    numberOfLoans++;
    
    //Create new loan object
    Loan myLoan(numberOfLoans);
    
    //Set the monthly payment on the loan
    myLoan.setPayment(monthlyPayment);
    
    //Set the monthly interest rate
    myLoan.setInterest(interestRate);
    
    //Set the principal amount
    myLoan.setPrincipal(principal);
    
    //Add the loan to the vector of loans
    myLoans.push_back(myLoan);
    
    //Output that you created a loan
    cout<<"Loan: "<<numberOfLoans<<" Created."<<endl<<endl;
}

void LoanManager::stringToTokens(string stringOfTokens, vector<string *> &arrayWithTokens)
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

string LoanManager::readLine(ifstream &myFile)
{
    string command = "";
    string tempString = "";
    getline(myFile, tempString);
    
    for (int length = 0; length < tempString.length(); length++)
    {
        if (tempString[length] == '/')
        {
            for (int counter = 0; counter < length; counter++)
            {
                command += tempString[counter];
            }
            break;
        }
    }
    if(validateCommand(command))
    {
        return command;
    }
    return "";
}

string LoanManager::getInputFileName()
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

//Deletes all of the Loan Classes
LoanManager::~LoanManager()
{
    exit(0);
    for(int loanCount = 0; loanCount < numberOfLoans; loanCount++)
    {
        myLoans[loanCount].~Loan();
    }
}
