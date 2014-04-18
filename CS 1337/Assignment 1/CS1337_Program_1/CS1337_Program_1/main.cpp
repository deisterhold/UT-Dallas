//
//  CS1337_Program_1
//
//  Created by Daniel Eisterhold on 1/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//
//  Loan Amortization Program
//  Reads input from file then outputs to another file
//  a loan amortization table
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

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

string getOutputFileName()
{
   string outputFileName; //Create String object to hold the output file location

   ofstream outputFile; //Create ofstream object to test if the file location is valid

   cout<<"Please enter a name for the output file Ex. \"Output.txt\" "<<endl;
   //Prompt the user to input the file location
   do
   {
       cin>>outputFileName; //Get the file location

       outputFile.open(outputFileName.c_str()); //Test openiong the file at the given location (Also creates the file)

       if (cin.fail() || !outputFile) //If getting the file location failed or unable to create the file
       {
           cout<<"Invalid File Name. Please Try Again: "<<endl;
           //Output error message
       }
       outputFile.close(); //Close the file
   }
   while (cin.fail() || !outputFile);
   //Repeat until the file is created successfully

   cout<<endl;
   //Line Space

   return outputFileName; //Return the valid file location
}

//Retrieves the number of loans needing to be processed
int getNumberOfLoans(string fileLocation) //Takes the file location as a parameter
{
   int numberOfTables = 0; //Number of Loan Amortization Tables to make
   ifstream inputFile; //Create ifstream object
   inputFile.open(fileLocation.c_str()); //Open the file

   inputFile>>numberOfTables; //Read the number of tables to make from the file

   inputFile.close(); //Close the input file

   return numberOfTables; //Return the value
}

//Retrieves information about each loan
void getLoanDetails(string fileLocation, double loans[][3], int numberOfLoans, int numberOfDetails = 3)
{
   ifstream inputFile(fileLocation.c_str());
   double tempNumber;
   inputFile>>tempNumber;

   for (int currentLoan = 0; currentLoan < numberOfLoans; currentLoan++)
   {
       for (int currentDetail = 0; currentDetail < numberOfDetails; currentDetail++)
       {
           inputFile>>loans[currentLoan][currentDetail];
       }
   }

}

void createLoanTable(ofstream& output,float monthlyPayment, float annualInterestRate, float loanAmount)
{
   //Declare variables
   double currentBalance = loanAmount;
   double monthlyInterestRate = annualInterestRate/12;
   double paymentInterest = 0.0;
   double totalInterest = 0.0;
   int currentPayment = 0;
   double payment = monthlyPayment;

   //Output Information about current Table
   cout<<setw(25)<<setfill(' ')<<left<<"Starting Balance:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<loanAmount<<endl;
   cout<<setw(25)<<setfill(' ')<<left<<"Annual Interest Rate:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(3)<<annualInterestRate<<endl;
   cout<<setw(25)<<setfill(' ')<<left<<"Monthly Payment:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<monthlyPayment<<endl;

   //Output Information about current Table to the file
   output<<setw(25)<<setfill(' ')<<left<<"Starting Balance:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<loanAmount<<endl;
   output<<setw(25)<<setfill(' ')<<left<<"Annual Interest Rate:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(3)<<annualInterestRate<<endl;
   output<<setw(25)<<setfill(' ')<<left<<"Monthly Payment:"<<setw(10)<<setfill(' ')<<right<<fixed<<setprecision(2)<<monthlyPayment<<endl;

   //Output the Column Names
   cout<<setw(12)<<right<<"Payment"<<setw(20)<<right<<"Amount"<<setw(12)<<right<<"Interest"
   <<setw(20)<<right<<"Principal"<<setw(20)<<right<<"Balance"<<endl;

   //Output the Column Names to the file
   output<<setw(12)<<right<<"Payment"<<setw(20)<<right<<"Amount"<<setw(12)<<right<<"Interest"
   <<setw(20)<<right<<"Principal"<<setw(20)<<right<<"Balance"<<endl;

   //If the current balance is greater than the monthly payment
   while ((currentBalance + (currentBalance*monthlyInterestRate)) >= monthlyPayment)
   {
       int tempNumber = 0;
       currentPayment++;
       paymentInterest = currentBalance*monthlyInterestRate;
       tempNumber = paymentInterest * 100;
       paymentInterest = (tempNumber/100.0);
       currentBalance -= (payment-paymentInterest);
       totalInterest += paymentInterest; //Calculate Total Interest Paid

       //Output one payment
       cout<<fixed<<setprecision(2)<<setw(12)<<right<<currentPayment<<setw(20)<<right<<payment<<setw(12)<<right<<paymentInterest
       <<setw(20)<<right<<payment-paymentInterest<<setw(20)<<right<<currentBalance<<endl;

       //Output one payment to the file
       output<<fixed<<setprecision(2)<<setw(12)<<right<<currentPayment<<setw(20)<<right<<payment<<setw(12)<<right<<paymentInterest
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

   //Output the last payment to the file
   output<<fixed<<setprecision(2)<<setw(12)<<right<<currentPayment<<setw(20)<<right<<payment<<setw(12)<<right<<paymentInterest
   <<setw(20)<<right<<payment-paymentInterest<<setw(20)<<right<<currentBalance<<"\n"<<endl;

   //Output the # of payments and Interest Paid
   cout<<"\nTotal Payments Made: "<<currentPayment<<endl;
   cout<<fixed<<setprecision(2)<<"Total Interest Paid: $"<<totalInterest<<endl;

   //Output the # of payments and Interest Paid to the file
   output<<"\nTotal Payments Made: "<<currentPayment<<endl;
   output<<fixed<<setprecision(2)<<"Total Interest Paid: $"<<totalInterest<<"\n"<<endl;

}

int main(int argc, const char * argv[])
{
   const int numberOfDetails = 3;

   string inputFileName = getInputFileName();
   string outputFileName = getOutputFileName();

   int numberOfLoans = getNumberOfLoans(inputFileName.c_str());

   double loans[numberOfLoans][numberOfDetails]; //Array to hold the data about the loans

   getLoanDetails(inputFileName, loans, numberOfLoans);

   ofstream outputFile;
   outputFile.open(outputFileName.c_str());

   //Loop through the loans and process the payments
   for (int currentLoan = 0; currentLoan < numberOfLoans; currentLoan++)
   {
       createLoanTable(outputFile, loans[currentLoan][2], loans[currentLoan][1], loans[currentLoan][0]);
   }

   //Close the file
   outputFile.close();

   return 0;
}
