//  CS1336.001
//  Assignment 5
//  GUI
//
//  Created by Daniel Eisterhold on 12/3/13.
//  Copyright (c) 2013 Daniel Eisterhold. All rights reserved.
//

#include <iostream>
#include <string> //Used for drawText
#include <algorithm> //Needed for reversing a string
#include <cmath> //Needed for Circle (Sin/Cos)

using namespace std;

#define SCREEN_WIDTH 79     //Sets Screen Width
#define SCREEN_HEIGHT 74    //Sets Screen Height
#define PI 3.14159          //Declare Pi (For drawCircle)

#include "graphics.h" //Header file with the Display Class

int main()
{
    Display myDisplay; //Creates Display Object called myDisplay
    
    //Function Examples
    //myDisplay.reset(); //Resets the function with blank spaces ' '
    
    //myDisplay.reset('b'); //Another reset function that initializes the array with a specified char;
    
    //myDisplay.drawLine(startingXPositionInt, startingYPositionInt, endingXPositionInt, endingYPositionInt);
    //or
    //myDisplay.drawLine(startingXPositionInt, startingYPositionInt, endingXPositionInt, endingYPositionInt, char);
    
    //myDisplay.drawRectangle( widthOfRectangleInt, heightOfRectangleInt, startingXPositionInt, startingYPositionInt);
    //or
    //myDisplay.drawRectangle( widthOfRectangleInt, heightOfRectangleInt, startingXPositionInt, startingYPositionInt, char);
    
    //myDisplay.drawText(startingXPositionInt, startingYPositionInt, endingXPositionInt, endingYPositionInt, string);
    
    //myDisplay.drawCircle(centerXPositionInt, centerYPositionInt, radiusInt);
    //or
    //myDisplay.drawCircle(centerXPositionInt, centerYPositionInt, radiusInt, char);
    
    myDisplay.reset(); //Resets the function with blank spaces ' '
    
    myDisplay.drawPixel(78, 73, '*');
    
    myDisplay.drawLine(0, 0, 0, 40); //Example Use of drawLine Function
    
    myDisplay.drawText(1, 5, 11, 5, "Hello World"); //Example Use of drawText Function (Includes drawTextDown)
    //Draws text between the given points whether horizontal or vertical
    //If the first point is lower than the second point text is reversed to be displayed backwards (Lower Level Ability)
    
    myDisplay.drawRectangle(6, 6, 20, 20, '&'); //Example Use of drawRectangle Function
    
    myDisplay.drawCircle(20,20,5); //Draws Circle
    
    myDisplay.displayScreen(); //Displays Screen on Command Line
    return 0;
}

