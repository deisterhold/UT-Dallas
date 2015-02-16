/*
Copyright (c) 2014, Daniel Eisterhold
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

class NumberPattern {
	//Declare values
	private int number1;
	private int number2;
	private int total;
	private int maxValue;

	public NumberPattern()
	{
		//Initialize Values
		this.number1 = 5;
		this.number2 = 7;
		this.total = 0;
		this.maxValue = 500;
	}

	public NumberPattern(int max)
	{
		//Initialize values
		this.number1 = 5;
		this.number2 = 7;
		this.total = 0;
		this.maxValue = max;
	}

	public void printPattern()
	{
		//Print out first two numbers
		System.out.print(this.number1);
		System.out.print(" ");
		System.out.print(this.number2);
		System.out.print(" ");
		
		//Loop until maximum value is reached
		while(this.total < this.maxValue) {
			if(this.total != 0) {
				//Print out the current total
				System.out.print(this.total);
				System.out.print(" ");
			}
			//Shift the numbers
			this.total = this.number1 + this.number2;
			this.number1 = this.number2;
			this.number2 = this.total;
		}
		
		System.out.println();
		//Print a new line
	}

	public static void main(String[] args) {
		NumberPattern myNumPat;
		//Create a NumberPattern object
		
		myNumPat = new NumberPattern();
		//Initialize the object
		
		//myNumPat = new NumberPattern(500);
		//You have the option of specifying the a value you do not want to exceed
		
		
		myNumPat.printPattern();
		//Print out the number pattern
	}
}
