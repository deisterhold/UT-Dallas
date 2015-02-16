/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.util.*;

class Box {
    
    int boxSize;
    
    public Box() {
        this.boxSize = 0;
    }
    
    public void drawBox() {
        //Get box dimensions
        this.boxSize = getInt("Please enter a number: ");
        
        //Print first line
        for(int x = 0; x < this.boxSize; x++) {
            System.out.print("*");
        }
        System.out.println(); //End line
        
        //Print lines on side
        for(int y = 1; y < (this.boxSize-1); y++) {
            System.out.print("*"); //Print left edge
            for(int x = 1; x < (this.boxSize-1); x++) {
                System.out.print(" "); //Print spaces in middle
            }
            System.out.println("*"); //Print right edge
        }
        
        //Print last line
        for(int x = 0; x < this.boxSize; x++) {
            System.out.print("*");
        }
        System.out.println(); //End line
    }
    
    private int getInt(String question) {
        Scanner input = new Scanner(System.in);
        
        //Create temporary variable
        int num = 0;
        
        //Create flag to know if loop has run
        boolean loopHasRun = false;
        
        //Loop until input is valid
        do {
            //Tell the user of the issue
            if(loopHasRun && (num < 3 || num > 20)) {
                System.out.println("Bad value!");
            }
            loopHasRun = true;
            
            //Prompt user
            System.out.print(question);
	    
            //Handle if invalid input
            while(!input.hasNextInt()) {
                System.out.println("Bad value!");
                System.out.print(question);
                input.nextLine();
                continue;
            }
                num = input.nextInt();
        }
        while(num < 3 || num > 20);
	
        return num;
    }
    
    public static void main(String[] args) {
        Box myBox = new Box();
        myBox.drawBox();
    }

}
