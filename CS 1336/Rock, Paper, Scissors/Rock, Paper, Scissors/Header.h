//
//  Header.h
//  Rock, Paper, Scissors
//
//  Created by Daniel Eisterhold on 10/29/13.
//  Copyright (c) 2013 Daniel Eisterhold. All rights reserved.
//

#ifndef Rock__Paper__Scissors_Header_h
#define Rock__Paper__Scissors_Header_h

//Outputs the menu & options for the user
void displayMenu()
{
    cout<<"\nGame Menu"<<endl;
    cout<<"---------"<<endl;
    cout<<"1) Rock"<<endl;
    cout<<"2) Paper"<<endl;
    cout<<"3) Scissors"<<endl;
    cout<<"4) Quit"<<endl;
}


//Simple encryption so the user can't edit the
//text file and increase their score
double encryptNumber(int numberToEncrypt, int encryptionKey = 1000)
{
    double encryptedNumber = 0.0;
    if (numberToEncrypt != 0) {
        encryptedNumber = encryptionKey/numberToEncrypt;
        double tempNumber = (encryptionKey % numberToEncrypt)/double(encryptionKey);
        encryptedNumber += tempNumber;
    }
    else
    {
        encryptedNumber = 0.0;
    }
    
    return encryptedNumber;
}
//Reverses the encryption so the user can't edit the
//text file and increase their score
//I don't like cheaters.
double decryptNumber(double numberToDecrypt, double encryptionKey = 1000)
{
    double decryptedNumber;
    if (numberToDecrypt != 0) {
        double tempNumber = numberToDecrypt-int(numberToDecrypt);
        numberToDecrypt -= tempNumber;
        tempNumber *= encryptionKey;
        encryptionKey -= tempNumber;
        decryptedNumber = encryptionKey/numberToDecrypt;
        decryptedNumber += .0000000001;
    }
    else
    {
        decryptedNumber = 0;
    }
    
    return decryptedNumber;
}


//Gets user input and then validates it
//if input is invalid it repeats
int getUserInput()
{
    int choice;
    do
    {
        cin>>choice;
        if(choice > 4 || choice < 1)
        {
            cout<<"Invalid Input. Enter a number between 1 and 4."<<endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    while (choice > 4 || choice < 1);
    return choice;
}


//Logic for the game
//Nested Switch statements yea!
void playGame(int currentGameScore[],int userChoice)
{
    int computerChoice = rand() % 3 + 1;
    switch (userChoice) {
        case 1:
            cout<<"You Selected: Rock"<<endl;
            switch (computerChoice) {
                case 1:
                    cout<<"The Computer Selected: Rock"<<endl;
                    cout<<"Tie. No Winner"<<endl;
                    break;
                case 2:
                    cout<<"The Computer Selected: Paper"<<endl;
                    cout<<"Computer Wins! Paper Wraps Rock"<<endl;
                    currentGameScore[1] += 1;
                    break;
                case 3:
                    cout<<"The Computer Selected: Scissors"<<endl;
                    cout<<"You Win! Rock Smashes Scissors"<<endl;
                    currentGameScore[0] += 1;
                    break;
            }
            break;
        case 2:
            cout<<"You Selected: Paper"<<endl;
            switch (computerChoice) {
                case 1:
                    cout<<"The Computer Selected: Rock"<<endl;
                    cout<<"You Win! Paper Wraps Rock"<<endl;
                    currentGameScore[0] += 1;
                    break;
                case 2:
                    cout<<"The Computer Selected: Paper"<<endl;
                    cout<<"Tie. No Winner"<<endl;
                    break;
                case 3:
                    cout<<"The Computer Selected: Scissors"<<endl;
                    cout<<"Computer Wins! Scissors Cuts Paper"<<endl;
                    currentGameScore[1] += 1;
                    break;
            }
            break;
        case 3:
            cout<<"You Selected: Scissors"<<endl;
            switch (computerChoice) {
                case 1:
                    cout<<"The Computer Selected: Rock"<<endl;
                    cout<<"Computer Wins! Rocks Smashes Scissors"<<endl;
                    currentGameScore[1] += 1;
                    break;
                case 2:
                    cout<<"The Computer Selected: Paper"<<endl;
                    cout<<"You Win! Scissors Cuts Paper"<<endl;
                    currentGameScore[0] += 1;
                    break;
                case 3:
                    cout<<"The Computer Selected: Scissors"<<endl;
                    cout<<"Tie. No Winner"<<endl;
                    break;
            }
            break;
        case 4:
            cout<<"Game is Quitting"<<endl;
            break;
            
        default:
            cout<<"Error."<<endl;
            break;
    }
    
}

//Saves the score for the game to a file named score.txt
bool writeToFile(int score[],string fileName = "score.txt")
{
    ofstream outputFile;
    double userScore = 0;
    double computerScore = 0;
    
    //Creates output file object
    outputFile.open(fileName.c_str());
    
    userScore = encryptNumber(score[0]);
    computerScore = encryptNumber(score[1]);
    
    //Writes data to file
    if(outputFile)
    {
        outputFile<<fixed<<setprecision(10)<<userScore<<endl;
        outputFile<<fixed<<setprecision(10)<<computerScore<<endl;
        return true;
    }
    else
    {
        cout<<"File was unable to be written to."<<endl;
        return false;
    }
    outputFile.close(); //Closes the file
}

//Reads in the score from previous games
bool readFile(int score[],string fileName = "score.txt")
{
    ifstream inputFile;
    double userScore = 0;
    double computerScore = 0;
    
    inputFile.open(fileName.c_str());
    
    //If file opened successfully read in the data
    if(inputFile)
    {
        inputFile>>userScore;
        inputFile>>computerScore;
        score[0] += decryptNumber(userScore);
        score[1] += decryptNumber(computerScore);
        //Output score from the previous games
        cout<<"User Score Read from File: "<<decryptNumber(userScore)<<endl;
        cout<<"Computer Score Read from File: "<<decryptNumber(computerScore)<<endl;
        return true;
    }
    else
    {
        return false;
    }
}

//Checks if the file already exists
//if not it then creates the file
bool createFile(string fileName = "score.txt")
{
    //File Manipulator
    ofstream newFile;
    ifstream existingFile;
    
    //Attempt
    existingFile.open(fileName.c_str());
    
    do {
        //Checks if file already exists
        if(existingFile)
        {
            cout<<"The file already exists."<<endl;
            existingFile.close();
            return true;
        }
        else
        {   //Creates file since it does not exist
            cout<<"The file does not exist"<<endl;
            newFile.open(fileName.c_str());
            if (newFile)
            {
                cout<<"The file has been created."<<endl;
                newFile<<encryptNumber(0)<<endl;
                newFile<<encryptNumber(0)<<endl;
                newFile.close();
                return true;
            }
            else
            {
                //Uh-oh something bad happened
                cout<<"Error. The file was unable to be opened or created!"<<endl;
                return false;
            }
            
        }
        //Loop until it behaves correctly
    } while (!existingFile && !newFile);
    return false;
}

#endif
