//
//  main.cpp
//  Rock, Paper, Scissors
//
//  Created by Daniel Eisterhold on 10/29/13.
//  Copyright (c) 2013 Daniel Eisterhold. All rights reserved.
//

/* READ THIS
 I created this application using XCode on OS X and the file system behaves differently on a mac.
 I believe to the best of my ability that this will work on a windows pc the way I have it currently set up,
 but it may not. If the program does not create an output file you will nead to adjust the parameters default argument
 of the createFile(), readFile(), and writeToFile(). I currently have the string set to "score.txt"
 Please change this string according to the directory that you need on windows
 For Example: "C:/Users/Username/Desktop/score.txt"
 */

#include <iostream>
#include <iomanip> //Library for manipulating IO
#include <fstream> //Library for file IO

using namespace std;

#include "Header.h" //Contains all of the games functions and logic


//Parallels Arrays too hold the score from the previous game
//And the other array is for the score of the current game
const int ARRAY_SIZE = 2;
int score[ARRAY_SIZE] = {0,0};
int currentGameScore[ARRAY_SIZE] = {0,0};

int main()
{
    //Variable to hold user input
    int choice;
    //If a file to permanently create scores
    //does not exist create one
    while(!createFile())
    {
        createFile();
    }
    //Read the score from the previous games
    readFile(score);
    
    
    //Continue playing the game until the user
    //decides to quit playing
    do
    {
        //Output the options the user can choose from
        displayMenu();
        
        //Sets value from return of function
        //The function validates the input
        choice = getUserInput();
        cout<<endl; //Create a new line
        
        //Logic of the game that determines who the winner is
        playGame(currentGameScore,choice);
    }
    while (choice != 4); //If the user has not selected to quit loop again

    //Total of the scores from the current game and
    //add that score to the total for all games played
    for (int index = 0; index < ARRAY_SIZE; index++) {
        score[index] += currentGameScore[index];
    }
    
    //Save the scores to the output file
    writeToFile(score);
    
    //Output the score for the current game and all games played
    cout<<endl; //Linebreak
    cout<<setw(30)<<left<<"User Wins"<<right<<currentGameScore[0]<<endl;
    cout<<setw(30)<<left<<"Computer Wins"<<right<<currentGameScore[1]<<endl;
    cout<<setw(30)<<left<<"Total User Wins"<<right<<score[0]<<endl;
    cout<<setw(30)<<left<<"Total Computer Wins"<<right<<score[1]<<endl;
    
    return 0;
}

