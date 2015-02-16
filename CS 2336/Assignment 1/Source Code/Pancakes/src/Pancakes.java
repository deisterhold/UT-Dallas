/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.util.*;

class Pancakes {
    //Declare variables
    float originalRadius;
    float originalQuantity;
    double originalArea;
    float newRadius;
    float newQuantity;
    double newArea;
    
    //Initialize variables to 0
    public Pancakes() {
        this.originalRadius = 0;
        this.originalQuantity = 0;
        this.originalArea = 0;
        this.newRadius = 0;
        this.newQuantity = 0;
        this.newArea = 0;
    }
    
    //Calculate the number of pancakes you can make
    public void calculateQuantity() {
        //Get input from user
        this.originalRadius = getFloat("Diameter of original pancakes (inches): ");
        this.originalQuantity = getFloat("Quantity of original pancakes: ");
        this.newRadius = getFloat("Diameter of new pancakes (inches): ");
	
        //Calculate the area of the two pancakes
        this.originalArea = this.originalQuantity * calculateArea(this.originalRadius);
        this.newArea = calculateArea(this.newRadius);
        
        //Calculate the number of pancakes
        this.newQuantity = (float)(this.originalArea/this.newArea);
	
        //Output the number you can make
        System.out.print("Quantity of new pancakes: ");
        System.out.format("%3.1f%n", (double)this.newQuantity);
    }
    
    //Calculates area
    private double calculateArea(float radius) {
        return Math.PI * radius * radius;
    }
    
    private float getFloat(String question) {
        Scanner input = new Scanner(System.in);
	
        float num = 0;
	
	do {
        //Promp user
	    System.out.print(question);
	    
        //Validate input
	    while(!input.hasNextFloat()) {
            //Giver user the error
	    	System.out.println("Please enter a floating point number.");
            System.out.print(question);
            input.nextLine();
            continue;
	    }
	    
            num = input.nextFloat();
        }
        while(num <= 0.0);
	
        return num;
    }
    
    public static void main(String[] args) {
        Pancakes myPancake = new Pancakes();
        myPancake.calculateQuantity();
    }

}
