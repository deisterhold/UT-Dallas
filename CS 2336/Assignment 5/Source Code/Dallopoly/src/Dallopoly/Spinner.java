/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//Make a Monopoly Package to group classes together
package Dallopoly;

//Import random number generator class
import java.util.Random;

//Class declaration
public class Spinner {
	
	//Create a random number generator
	private Random randGen;
	//Create array of the possible values to return
	private int[] values = {1,2,3,4,5,-1,-2,-3};
	
	//Default constructor
	public Spinner() {
		//Initialize random number generator
		this.randGen = new Random();
		//Set the seed of the random number generator as the current time in milliseconds
		this.randGen.setSeed(System.currentTimeMillis());
	}
	
	public int spin() {
		//Create variable and store in it a random number between 0 (inclusive) and the length of the array (exclusive)
		int randomNumber = this.randGen.nextInt(this.values.length);
		//Return a random value in the array using the variable created above
		return this.values[randomNumber];
	}
}
