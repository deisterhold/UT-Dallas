//
//  Loan.h
//  CS_1337_Assignment_3
//
//  Created by Daniel Eisterhold on 2/27/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS_1337_Assignment_3__Loan__
#define __CS_1337_Assignment_3__Loan__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Loan
{
public:
    //Constructor
    Loan(int);
    
    //Destructor
    ~Loan();
    
    //Set the loan properties
    void setInterest(double);
    void setPrincipal(double);
    void setPayment(double);
    
    //Get Information about the loan
    double getPayment(int) const;
    double getInterest(int) const;
    double getPrincipal() const;
    double getBalance(int) const;
    void showHistory() const;
    
    //Manipulate the loan
    void makePayment(double);
    void printAmortizationTable();
    void calculatePayoff();
    
    int getNumberOfPayments();
    int numberOfPayments;
private:
    vector<double> loanPayment;
    vector <vector<double>> loanTable;
    bool principalSet = false;
    bool interestSet = false;
    bool paymentSet = false;
    int loanNumber = 0;
};

#endif /* defined(__CS_1337_Assignment_3__Loan__) */