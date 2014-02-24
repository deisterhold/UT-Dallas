//
//  graphics.h
//  GUI
//
//  Created by Daniel Eisterhold on 12/3/13.
//  Copyright (c) 2013 Daniel Eisterhold. All rights reserved.
//

#ifndef GUI_graphics_h
#define GUI_graphics_h
class Display
{
    char screen[SCREEN_WIDTH][SCREEN_HEIGHT];
    //Declare and Initialize the Character array that will be acting as a pixel display
    
    //Declare the constants for use within the class
    const char ON = '*'; //Fill character for drawing
    const char OFF = ' '; //Blank character for clearing the screen
    const char ERROR = '?'; //Character for Invalid Data
    const char NONE = '\0'; //Character if there is no data
    const int MIN_X = 0; //Minimum value off the X Axis on the Pixel Array
    const int MIN_Y = 0; //Minimum value off the Y Axis on the Pixel Array
    const int MAX_X = (SCREEN_WIDTH-1); //Maximum value off the X Axis on the Pixel Array
    const int MAX_Y = (SCREEN_HEIGHT-1); //Maximum value off the Y Axis on the Pixel Array
    
private:
    bool validPosition(char screen[][SCREEN_HEIGHT], int xPos, int yPos)
    //Checks if a point is valid in the array
    {
        if(xPos >= MIN_X && xPos <= MAX_X)
        //Checks if in range on x axis
        {
            if(yPos >= MIN_Y && yPos <= MAX_Y)
            //Checks if in range on y axis
            {
                return true;
                //If so return true
            }
            //Else return false
            return false;
        }
        return false;
    }
    
    bool isHorizontal(int xPos, int yPos, int secondX, int secondY)
    //Checks to see if the line to be drawn is horizontal
    {
        if(yPos == secondY)
        //If the y coordinates match (Vertical Line)
        {
            return true;
        }
        return false;
    }
    
    bool isVertical(int xPos, int yPos, int secondX, int secondY)
    //Checks to see if the line to be drawn is horizontal
    {
        if(xPos == secondX)
        //If the x coordinates match (Horizontal Line)
        {
            return true;
        }
        return false;
    }

public:
    //Fill in the array with a specified value or '*'
    void reset(char pixel = ' ')
    {
        for (int x = 0; x <= MAX_X; x++)
        {
            for (int y = 0; y <= MAX_Y; y++)
            {
                this->drawPixel(x, y, pixel);
            }
        }
    }

    void displayScreen()
    {
        cout<<endl;
        for (int y = 0; y <= MAX_Y; y++)
        {
            for (int x = 0; x <= MAX_X; x++)
            {
                cout<<screen[x][y];
            }
            cout<<endl;
        }
    }

    void drawPixel(int xPos, int yPos, char pixel)
    {
        if(validPosition(screen, xPos, yPos))
        {
            screen[xPos][yPos] = pixel;
        }
        //cout<<"Drawing Pixel"<<endl;
        
    }

    void drawLine(int xPos, int yPos, int secondX, int secondY, char letter = '*')
    {
        if (isVertical(xPos, yPos, secondX, secondY))
        {
            if(yPos > secondY)
            {
                int temp = yPos;
                yPos = secondY;
                secondY = temp;
            }
            for (int currentY = yPos; currentY <= secondY; currentY++)
            {
                drawPixel(xPos, currentY, letter);
            }
        }
        else if (isHorizontal(xPos, yPos, secondX, secondY))
        {
            if(xPos > secondX)
            {
                int temp = xPos;
                xPos = secondX;
                secondX = temp;
            }
            for (int currentX = xPos; currentX <= secondX; currentX++)
            {
                drawPixel(currentX, yPos, letter);
            }
        }
        else
        {
            drawPixel(xPos, yPos, ERROR);
            drawPixel(secondX, secondY, ERROR);
        }
    }

    void drawRectangle(int width, int height, int xPos, int yPos, char letter = '*')
    {
        drawLine(xPos, yPos, xPos, yPos+height, letter); //Left Side
        drawLine(xPos+width, yPos, xPos+width, yPos+height, letter); //Right Side
        drawLine(xPos, yPos, xPos+width, yPos, letter); //Top Side
        drawLine(xPos, yPos+height, xPos+width, yPos+height, letter); //Bottom Side
    }

    void drawText(int xPos, int yPos, int secondX, int secondY, string word)
    {
        int length = int(word.length());
        if (isVertical(xPos, yPos, secondX, secondY))
        {
            if(yPos > secondY)
            {
                int temp = yPos;
                yPos = secondY;
                secondY = temp;
                reverse(word.begin(), word.end());
            }
            for (int currentY = yPos, letter = 0; currentY <= secondY && letter < length; currentY++, letter++)
            {
                drawPixel(xPos, currentY, word[letter]);
            }
        }
        else if (isHorizontal(xPos, yPos, secondX, secondY))
        {
            if(xPos > secondX)
            {
                int temp = xPos;
                xPos = secondX;
                secondX = temp;
                reverse(word.begin(), word.end());
            }
            for (int currentX = xPos, letter = 0; currentX <= secondX && letter < length; currentX++, letter++)
            {
                drawPixel(currentX, yPos, word[letter]);
            }
        }
        else
        {
            drawPixel(xPos, yPos, ERROR);
            drawPixel(secondX, secondY, ERROR);
        }
    }
    
    char getPixel(int xPos, int yPos)
    //Function that gets the pixel that is currently at a certain
    //coordinate in the array
    {
        if (validPosition(screen, xPos, yPos)) {
            return screen[xPos][yPos];
        }
        
        return NONE;
    }
    
    void drawCircle(int xPos, int yPos, int radius, char pixel = '*')
    {
        //Variables to hold the points for drawing the circle
        int circumferenceX;
        int circumferenceY;
        //Loops through all the angles of a circle (360 Degrees)
        for (int angle = 0; angle < 360; angle++) {
            circumferenceX = radius * cos(angle*PI/180); //Determines X Coordinates
            circumferenceY = radius * sin(angle*PI/180); //Determines Y Coordinates (the PI/180 is to convert to radians)
            drawPixel(xPos+circumferenceX, yPos+circumferenceY, pixel); //Draws the circle
        }
    }
};

#endif
