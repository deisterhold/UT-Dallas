//
//  LoanManager.h
//  CS_1337_Assignment_3
//
//  Created by Daniel Eisterhold on 3/19/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS_1337_Assignment_3__LoanManager__
#define __CS_1337_Assignment_3__LoanManager__

#include "Loan.h"
#include <cstring>

class LoanManager
{
public:
    LoanManager();
    ~LoanManager();
    void readFile(ifstream &);
    
private:
    string getInputFileName();
    
    bool validateCommand(string);
    void processCommand(string);
    void stringToTokens(string, vector<string *> &);
    void createNewLoan(double, double, double);
    string readLine(ifstream &);
    
    string inputFileName = "";
    string outputFileName = "";
    int numberOfLoans = 0;
    vector<Loan> myLoans;
};
#endif /* defined(__CS_1337_Assignment_3__LoanManager__) */
