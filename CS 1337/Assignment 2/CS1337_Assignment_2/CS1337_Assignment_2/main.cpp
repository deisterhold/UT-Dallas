//
//  CS1337_Assignment_2
//
//  Created by Daniel Eisterhold on 2/13/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

const bool debug = true;

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

string getSearchTerm()
{
    string searchTerm = ""; //Create variable to hold the data
    
    do
    {
        //Ask user for what they want to search
        cout<<"Please enter the term: ";
        cin>>searchTerm;
    } while (cin.fail() || searchTerm.length() < 1);
    //Do some simple error checking
    
    cout<<endl; //Add an extra line
    
    return searchTerm;
}

int getUserMenuSelection(int numberOfOptions)
{
    int selection = -1; //Intizialize to an invalid value
    
    //Do while loop because it is a menu
    do
    {
        cout<<"Please choose a menu option: "; //Ask user for input
        cin>>selection; //Read in input
        
        if (cin.fail()) //Reading in user selection failed
        {
            cout<<"Failure Invalid Input. Ex. 1-"<<numberOfOptions<<endl; //Tell user that it is invalid and the valid range
            cin.clear(); //Clear the input stream
            cin.ignore(1000, '\n'); //Ignore any characters that could cause cin to fail
            selection = -1; //Set selection back to its intitial value
        }
        
        if ((selection < 1) || (selection > numberOfOptions))
        {
            cout<<"Invalid Input! Ex. 1-"<<numberOfOptions<<endl; //Tell user that it is invalid and the valid range
            cin.clear(); //Clear the input stream
            cin.ignore(1000, '\n'); //Ignore any characters that could cause cin to fail
            selection = -1;
        }
        
    } while ((selection < 1) || (selection > numberOfOptions));
    //Repeat until the user input is valid
    
    cout<<endl; //Add a new line after the user inputs valid data
    
    return selection;
}

void displayArray(const string lastName[], const string firstName[], const string birthDate[], const int lengthOfArray, const int order[], const bool ascending = true)
{
    //Output to the command line the names of what you are displaying (left aligned & constant width)
    cout<<left<<setw(20)<<"First Name"<<setw(20)<<"Last Name"<<setw(10)<<"Birth Date"<<endl;
    if (ascending)
    {
        for (int currentPerson = 0; currentPerson < lengthOfArray; currentPerson++)
        {
            if (order[currentPerson] == -1) break;
            cout<<left<<setw(20)<<firstName[order[currentPerson]]<<setw(20)<<lastName[order[currentPerson]]<<setw(10)<<birthDate[order[currentPerson]]<<endl;
        }
    }
    else
    {
        for (int currentPerson = (lengthOfArray-1); currentPerson >= 0; currentPerson--)
        {
            if (order[currentPerson] == -1) break;
            cout<<left<<setw(20)<<firstName[order[currentPerson]]<<setw(20)<<lastName[order[currentPerson]]<<setw(10)<<birthDate[order[currentPerson]]<<endl;
        }
    }
    
    cout<<endl; //Add an extra line after displaying the array
}

bool readInFile(ifstream & inputFile, string personLastName[], string personFirstName[], string personBirthDate[], const int length)
{
    //Read in the first name, last name, and birth date for the number of people specified
    for (int currentPerson = 0; currentPerson < length; currentPerson++)
    {
        //Read in the last name then first name then birth date
        inputFile>>personLastName[currentPerson]>>personFirstName[currentPerson]>>personBirthDate[currentPerson];
    }
    
    //If the end of file has been reached then you have successfully read all of the data in the file
    if (inputFile.eof())
    {
        //return that you have successfully read the file
        return true;
    }
    
    //return that you were unable to read the entire file
    return false;
}

int displayMainMenu()
{
    //Outputs the main menu
    cout<<"1. Sorting"<<endl;
    cout<<"2. Searching"<<endl;
    cout<<"3. Quit"<<endl;
    return getUserMenuSelection(3);
}

int displaySearchMenu()
{
    //Outputs the search menu
    cout<<"Search by:"<<endl;
    cout<<"1. First Name"<<endl;
    cout<<"2. Last Name"<<endl;
    cout<<"3. Birth Date"<<endl;
    cout<<"4. Back"<<endl;
    return getUserMenuSelection(4);
}

int displaySortMenu()
{
    //Outputs the menu
    cout<<"Sort by:"<<endl;
    cout<<"1. First Name"<<endl;
    cout<<"2. Last Name"<<endl;
    cout<<"3. Birth Date"<<endl;
    cout<<"4. Back"<<endl;
    return getUserMenuSelection(4);
}

int displayOrderMenu()
{
    //Outputs the menu
    cout<<"Sort:"<<endl;
    cout<<"1. Ascending (A,B,C)"<<endl;
    cout<<"2. Descending (Z,Y,X)"<<endl;
    return getUserMenuSelection(2);
}

void copyStringArray(const string arrayToCopy[], string copyOfArray[], int arrayLength)
{
    //Duplicates an array so that I can sort
    for (int subscript = 0; subscript < arrayLength; subscript++)
    {
        copyOfArray[subscript] = arrayToCopy[subscript];
    }
}

void sortAscending(const string stringToSort[], int arrayToSortInt[],int length)
{
    string *arrayToSort = new string[length];
    copyStringArray(stringToSort, arrayToSort, length);
    
    string temporaryString; //Holds the lowest value
    int currentIndex = 0; //Holds subscript of element
    int temporaryInt;
    int currentIndexInt = 0; //Parallel the two above for the int array
    
    //Loop through until all elements are sorted
    for (int numberOfItemsSorted = 0; numberOfItemsSorted < (length); numberOfItemsSorted++)
    {
        temporaryString = arrayToSort[numberOfItemsSorted];
        temporaryInt = arrayToSortInt[numberOfItemsSorted];
        //Put the first element of the elements you want to store into a string
        
        bool foundLowest = false; //Flag stating you found the lowest value
        
        //Loop through until you find the lowest element in the entire array
        for (int index = (numberOfItemsSorted+1); index<length; index++)
        {
            if (temporaryString > arrayToSort[index]) //Trying to find the lowest string
            {
                temporaryInt = arrayToSortInt[index];
                temporaryString = arrayToSort[index]; //Set this to the lowest valued string
                currentIndexInt = index;
                currentIndex = index; //Remember where that lowest value is
                foundLowest = true; //Set flag that you found the lowest value
            }
        }
        
        if (foundLowest)
        {
            //If found  the lowest value swap the value
            arrayToSort[currentIndex] = arrayToSort[numberOfItemsSorted];
            arrayToSort[numberOfItemsSorted] = temporaryString;
            
            //Swap integer array
            arrayToSortInt[currentIndexInt] = arrayToSortInt[numberOfItemsSorted];
            arrayToSortInt[numberOfItemsSorted]= temporaryInt;
        }
        else
        {
            //If the lowest value was not found
            arrayToSort[numberOfItemsSorted] = temporaryString;
            //Do again for the parallel int array
            arrayToSortInt[numberOfItemsSorted] = temporaryInt;
        }
    }
}

void searchArray(const string arrayToSearch[], const string termToSearch, int arrayLength, int itemsFound[])
{
    int numberOfItemsFound = 0;
    
    //Initialize the array to -1 (Invalid Subscript Values)
    for (int counter = 0; counter < arrayLength; counter++)
    {
        itemsFound[counter] = -1;
    }
    
    for (int currentElement = 0; currentElement < arrayLength; currentElement++)
    {
        int letterCounter = 0;
        
        for (int letter = 0 ; letter < termToSearch.length(); letter++) {
            if (termToSearch[letter] == arrayToSearch[currentElement][letter])
            {
                letterCounter++;
            }
        }
        if (letterCounter == termToSearch.length()) {
            itemsFound[numberOfItemsFound] = currentElement;
            numberOfItemsFound++;
        }
    }
    //Tell how many terms were found
    cout<<"Found "<<numberOfItemsFound<<endl<<endl;
}

int main(int argc, const char * argv[])
{
    //Get the file location from the user
    string inputFile;
    if (debug)
    {
        inputFile = "/Users/deisterhold/Desktop/input.txt";
    }
    else
    {
        inputFile = getInputFileName();
    }
    
    int lengthOfArray = -1; //Create int to hold the length of the array (Initialize to invalid array subscript)
    
    ifstream input; //Create file object

    //Create a pointer that holds the address of the parallel arrays
    string * lastName  = nullptr;
    string * firstName = nullptr;
    string * birthDate = nullptr;
    
    //Create point that holds the address of the sorted arrays
    int * sortLastName  = nullptr; //Holds the last names in ascending order
    int * sortFirstName = nullptr; //Holds the first names in ascending order
    int * sortBirthDate = nullptr; //Holds the birth dates in ascending order
    
    input.open(inputFile.c_str()); //Open the file
    
    //Get from the file the number of items to read
    input>>lengthOfArray;
    
    //If there exists data to be read in
    if(lengthOfArray >= 1)
    {
        //Create all of the arrays and set the respective pointers to those array locations
        lastName = new string[lengthOfArray];
        firstName = new string[lengthOfArray];
        birthDate = new string[lengthOfArray];
        sortLastName = new int[lengthOfArray];
        sortFirstName = new int[lengthOfArray];
        sortBirthDate = new int[lengthOfArray];
        
        //Initialize all of the arrays
        for (int element = 0; element < lengthOfArray; element++) {
            lastName[element]  = " ";
            firstName[element] = " ";
            birthDate[element] = " ";
            sortLastName[element] = element;
            sortFirstName[element] = element;
            sortBirthDate[element] = element;
        }
    }
    
    //Read in the file and make sure it has completed successfully
    if(!readInFile(input, lastName, firstName, birthDate, lengthOfArray))
    {
        /*
         If the file was unable to be read then exit with an error code
         because you really can't do anything else
         */
        cout<<"Unable to read file"<<endl;
        exit(1);
    }
    
    input.close(); //Close the input file!!!
    
    //Run once and done because no new data is added
    sortAscending(firstName, sortFirstName, lengthOfArray);
    sortAscending(lastName, sortLastName, lengthOfArray);
    sortAscending(birthDate, sortBirthDate, lengthOfArray);
    
    int foundTerms[lengthOfArray]; //Array to hold the number of items found in the search
    
    //Infinitely loops until user chooses to exit
    while (true)
    {
    mainMenu:
        switch (displayMainMenu()) {
            case 1:
                switch (displaySortMenu())
                    {
                    case 1:
                        switch(displayOrderMenu())
                        {
                            case 1:
                                displayArray(lastName, firstName, birthDate, lengthOfArray, sortFirstName);
                                break;
                            case 2:
                                displayArray(lastName, firstName, birthDate, lengthOfArray, sortFirstName, false);
                                break;
                        }
                        break;
                    case 2:
                        switch(displayOrderMenu())
                        {
                        case 1:
                            displayArray(lastName, firstName, birthDate, lengthOfArray, sortLastName);
                            break;
                        case 2:
                            displayArray(lastName, firstName, birthDate, lengthOfArray, sortLastName, false);
                            break;
                        }
                        break;
                    case 3:
                        switch(displayOrderMenu())
                        {
                        case 1:
                            displayArray(lastName, firstName, birthDate, lengthOfArray, sortBirthDate);
                            break;
                        case 2:
                            displayArray(lastName, firstName, birthDate, lengthOfArray, sortBirthDate, false);
                            break;
                        }
                        break;
                    case 4:
                        goto mainMenu;
                        break;
                    default:
                        exit(0);
                        break;
                    }
                break;
            case 2:
                switch(displaySearchMenu())
                    {
                    case 1:
                        //Search First Name
                        searchArray(firstName, getSearchTerm(), lengthOfArray, foundTerms);
                        displayArray(lastName, firstName, birthDate, lengthOfArray, foundTerms);
                        break;
                    case 2:
                        //Search Last Name
                        searchArray(lastName, getSearchTerm(), lengthOfArray, foundTerms);
                        displayArray(lastName, firstName, birthDate, lengthOfArray, foundTerms);
                        break;
                    case 3:
                        //Search Birth Date
                        searchArray(birthDate, getSearchTerm(), lengthOfArray, foundTerms);
                        displayArray(lastName, firstName, birthDate, lengthOfArray, foundTerms);
                        break;
                    case 4:
                        goto mainMenu;
                        break;
                    default:
                        exit(0);
                        break;
                    }
                break;
            case 3:
                exit(0); //Program Ended Successfully
                break;
            default:
                cout<<"Invalid data was returned"<<endl;
                exit(1);
                break;
        }
    }
    
    return 0;
}

