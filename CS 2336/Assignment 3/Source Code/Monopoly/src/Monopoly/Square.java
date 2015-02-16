/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//Make a Monopoly Package to group classes together
package Monopoly;

//Class declaration
public class Square {
	//Create a variable to hold the name of the square
	private String label;
	
	//Default constructor
	public Square() {
		//Initialize the label variable
		this.label = new String();
	}
	
	//Constructor with option to set the name of the square
	public Square(String newLabel) {
		//Call the default constructor
		this();
		//Pass name to the method to set the name
		this.setLabel(newLabel);
	}
	
	public void setLabel(String newLabel) {
		//Set the passed in string to be the name of the square
		this.label = newLabel;
	}
	
	public String getLabel() {
		//Return the name of the square
		return this.label;
	}
	
	//Override 'toString()' method from Object
	public String toString() {
		//Return details about the object
		return new String("Square named: " + this.label);
	}
}
