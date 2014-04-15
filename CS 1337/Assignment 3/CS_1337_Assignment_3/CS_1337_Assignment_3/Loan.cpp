//
//  Loan.cpp
//  CS_1337_Assignment_3
//
//  Created by Daniel Eisterhold on 2/27/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "Loan.h"

#define PAYMENT     0
#define INTEREST    1
#define BALANCE     2

using namespace std;

//Constructor
Loan::Loan(int loanNum)
{
    numberOfPayments = 0;
    
    loanPayment.resize(3);
    loanPayment[0] = 0;
    loanPayment[1] = 0;
    loanPayment[2] = 0;
    
    loanTable.push_back(loanPayment);
    
    loanNumber = loanNum;
//    cout<<"Loan: "<<numberOfLoans<<" Created"<<endl;
}

//Set the loan interest
void Loan::setInterest(double interestRate)
{
    if (!interestSet)
    {
        interestSet = true;
        loanTable[0][INTEREST] = (interestRate/12.0);
        cout<<"Loan: "<<loanNumber<<"- Interest rate has been set to a annual rate of: "
        <<fixed<<setprecision(2)<<loanTable[0][INTEREST]*1200<<"%"<<endl;
    }
    else
    {
        loanTable.resize(loanTable.size()+1,
                         loanPayment =
         {
                                        loanTable[loanTable.size()-1][PAYMENT],
                                        loanTable[loanTable.size()-1][INTEREST],
                                        loanTable[loanTable.size()-1][BALANCE]
         });
        loanTable[loanTable.size()-1][INTEREST] = (interestRate/12.0);
        cout<<"Loan: "<<loanNumber<<"- Interest rate has been set to a annual rate of: "
        <<fixed<<setprecision(2)<<loanTable[loanTable.size()-1][INTEREST]*1200<<"%"<<endl;
    }
}

//Set the monthly interest rate
void Loan::setPrincipal(double startingAmount)
{
    if (!principalSet)
    {
        principalSet = true;
        loanTable[0][BALANCE] = startingAmount;
        cout<<"Loan: "<<loanNumber<<"- Principal set to: $"<<loanTable[0][BALANCE]<<endl;
    }
    else
    {
        cout<<"Principal has already been set and cannot be changed."<<endl;
    }
}

//Set loan payment amount
void Loan::setPayment(double paymentAmount)
{
    if (!paymentSet)
    {
        paymentSet = true;
        loanTable[0][PAYMENT] = paymentAmount;
        cout<<"Loan: "<<loanNumber<<"- Payment has been set to a monthly rate of: $"<<loanTable[0][PAYMENT]<<endl;
    }
    else
    {
        loanTable.resize(loanTable.size()+1, loanPayment =
        {   loanTable[loanTable.size()-1][PAYMENT]
            ,loanTable[loanTable.size()-1][INTEREST],
            loanTable[loanTable.size()-1][BALANCE]
        });
        
        loanTable[loanTable.size()-1][PAYMENT] = paymentAmount;
        cout<<"Loan: "<<loanNumber<<"- Payment has been set to a monthly rate of: $"<<loanTable[loanTable.size()-1][PAYMENT]<<endl;
    }
}

//Get Information about the loan
double Loan::getPayment(int paymentNumber = -1) const
{
    if (paymentNumber < loanTable.size() && paymentNumber >= 0)
    {
        return loanTable[paymentNumber][PAYMENT];
    }
    else
    {
        return -1.0;
    }
}

//Get the last (or specified) interest rate of the loan
double Loan::getInterest(int paymentNumber = 0) const
{
    if (paymentNumber <= loanTable.size() && paymentNumber >= 0)
    {
        return loanTable[paymentNumber][INTEREST];
    }
    return -1.0;
}

//Get the starting amount of the loan
double Loan::getPrincipal() const
{
    return loanTable[0][BALANCE];
}

//Get the remaining balance
double Loan::getBalance(int payment = -1) const
{
    if(payment >= 0 && payment < loanTable.size())
    {
        return loanTable[payment][BALANCE];
    }
    return loanTable[loanTable.size()][BALANCE];
}

void Loan::showHistory() const
{
    cout<<"Showing history of loan "<<loanNumber<<endl;
    //Output Information about current Table
    cout<<setw(25)<<setfill(' ')<<left<<"Starting Balance:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<loanTable[0][BALANCE]<<endl;
    cout<<setw(25)<<setfill(' ')<<left<<"Annual Interest Rate:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(3)<<loanTable[0][INTEREST]<<endl;
    cout<<setw(25)<<setfill(' ')<<left<<"Monthly Payment:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<loanTable[0][PAYMENT]<<endl;
    
    //Output the Column Names
    cout<<setw(12)<<right<<"Payment"<<setw(20)<<right<<"Amount"<<setw(12)<<right<<"Interest"
    <<setw(20)<<right<<"Balance"<<endl;
    
    //If the current balance is greater than the monthly payment
    for (int paymentNumber = 0; paymentNumber < loanTable.size(); paymentNumber++)
    {
        //Output one payment
        cout<<fixed<<setprecision(2)<<setw(12)<<right<<paymentNumber<<setw(20)<<right<<loanTable[paymentNumber][PAYMENT]<<setw(12);
        cout<<right<<loanTable[paymentNumber][INTEREST]<<setw(20)<<right<<loanTable[paymentNumber][BALANCE]<<endl;
    }
    
    //Output the # of payments and Interest Paid
    cout<<"\nTotal Payments Made: "<<loanTable.size()-1<<endl<<endl;
}

//Make a payment on the loan
void Loan::makePayment(double paymentAmount)
{
    
    //Declare variables
    double currentBalance = loanTable[loanTable.size()-1][BALANCE];
    double monthlyInterestRate = loanTable[loanTable.size()-1][INTEREST];
    double payment = paymentAmount;
    
    //Calculate the payment
    int paymentInterest = currentBalance*monthlyInterestRate;
    
    //Only use two decimal places
    int tempNumber = 0;
    tempNumber = paymentInterest * 100;
    paymentInterest = (tempNumber/100.0);
    
    //Calculate new balance
    currentBalance -= (payment-paymentInterest);
    
    //Create payment
    loanPayment = {paymentAmount, monthlyInterestRate, currentBalance};
    
    //Add payment to vector
    loanTable.push_back(loanPayment);
    
    cout<<"You made a $"<<paymentAmount<<" payment."<<endl<<endl;
}

void Loan::printAmortizationTable()
{
    //Declare variables
    double currentBalance = loanTable[loanTable.size()-1][BALANCE];
    double monthlyInterestRate = loanTable[loanTable.size()-1][INTEREST];
    double paymentInterest = 0.0;
    double totalInterest = 0.0;
    int currentPayment = 0;
    double payment = loanTable[loanTable.size()-1][PAYMENT];
    
    cout<<endl;
    //Output Information about current Table
    cout<<setw(25)<<setfill(' ')<<left<<"Starting Balance:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<loanTable[loanTable.size()-1][BALANCE]<<endl;
    cout<<setw(25)<<setfill(' ')<<left<<"Annual Interest Rate:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(3)<<loanTable[loanTable.size()-1][INTEREST]*12<<endl;
    cout<<setw(25)<<setfill(' ')<<left<<"Monthly Payment:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<loanTable[loanTable.size()-1][PAYMENT]<<endl;
    
    //Output the Column Names
    cout<<setw(12)<<right<<"Payment"<<setw(20)<<right<<"Amount"<<setw(12)<<right<<"Interest"
    <<setw(20)<<right<<"Principal"<<setw(20)<<right<<"Balance"<<endl;
    
    //If the current balance is greater than the monthly payment
    while ((currentBalance + (currentBalance*monthlyInterestRate)) >= loanTable[loanTable.size()-1][PAYMENT])
    {
        int tempNumber = 0;
        currentPayment++;
        paymentInterest = currentBalance*monthlyInterestRate;
        
        //Remove any more than two decimals (because dealing with USD)
        tempNumber = paymentInterest * 100;
        paymentInterest = (tempNumber/100.0);
        
        //Subtract payment without interest from balance
        currentBalance -= (payment-paymentInterest);
        totalInterest += paymentInterest; //Calculate Total Interest Paid
        
        //Output one payment
        cout<<fixed<<setprecision(2)<<setw(12)<<right<<currentPayment<<setw(20)<<right<<payment<<setw(12)<<right<<paymentInterest
        <<setw(20)<<right<<payment-paymentInterest<<setw(20)<<right<<currentBalance<<endl;
    }
    
    //Calculate the last payment
    currentPayment++;
    paymentInterest = currentBalance*monthlyInterestRate;
    payment = paymentInterest + currentBalance;
    currentBalance -= (payment-paymentInterest);
    totalInterest += paymentInterest;
    
    //Output the last payment
    cout<<fixed<<setprecision(2)<<setw(12)<<right<<currentPayment<<setw(20)<<right<<payment<<setw(12)<<right<<paymentInterest
    <<setw(20)<<right<<payment-paymentInterest<<setw(20)<<right<<currentBalance<<"\n"<<endl;
    
    //Output the # of payments and Interest Paid
    cout<<"\nTotal Payments Made: "<<currentPayment<<endl;
    cout<<fixed<<setprecision(2)<<"Total Interest Paid: $"<<totalInterest<<endl<<endl;
}

void Loan::calculatePayoff()
{
    //Declare variables
    double currentBalance = loanTable[0][BALANCE];
    double monthlyInterestRate = loanTable[0][INTEREST];
    double paymentInterest = 0.0;
    int currentPayment = 0;
    
    //Output the Column Names
    cout<<"If you were to payoff the remaining balance right now you would owe:\n$";
    
    paymentInterest = currentBalance*monthlyInterestRate;
    currentPayment = paymentInterest + currentBalance;
    
    //Output the payoff amount
    cout<<fixed<<setprecision(2)<<currentPayment<<endl;
}

Loan::~Loan()
{
    
}