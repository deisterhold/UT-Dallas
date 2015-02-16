/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package Monopoly;

public class SimpleMonopoly {
	
	private int currentSquareNumber;
	private Square[] squares;
	private Spinner theSpinner;
	
	public SimpleMonopoly() {
		this.squares = new Square[16];
		this.squares[0] = new Square("White (GO)");
		this.squares[1] = new Square("Red");
		this.squares[2] = new Square("Blue");
		this.squares[3] = new Square("Green");
		this.squares[4] = new Square("Yellow");
		this.squares[5] = new Square("Red");
		this.squares[6] = new Square("Blue");
		this.squares[7] = new Square("Green");
		this.squares[8] = new Square("Yellow");
		this.squares[9] = new Square("Red");
		this.squares[10] = new Square("Blue");
		this.squares[11] = new Square("Green");
		this.squares[12] = new Square("Yellow");
		this.squares[13] = new Square("Red");
		this.squares[14] = new Square("Blue");
		this.squares[15] = new Square("Green");
		this.theSpinner = new Spinner();
		this.setCurrentSquare(0);
	}
	
	public void setCurrentSquare(int newSquareNumber) {
		//Make sure that the new position is within the valid range
		newSquareNumber %= this.squares.length;
		
		//Set new position
		this.currentSquareNumber = newSquareNumber;
	}
	
	public int getCurrentSquare() {
		//Return position of the square
		return this.currentSquareNumber;
	}
	
	public void playGame() {
		//Output that the game is starting
		System.out.println("Iron is starting on GO square #0");
		for(int spinNumber = 0; spinNumber < 10; spinNumber++) {
			//Spin the spinner to get the number of positions to move
			int numRolled = this.theSpinner.spin();
			
			//Store the position so that it won't have to be called multiple times in the following code
			int position = this.getCurrentSquare();
			
			//Set the current position to the old position plus the number of positions to move
			this.setCurrentSquare(position + numRolled);
			
			//Set position to the new position
			position = this.getCurrentSquare();
			
			//Output the number rolled, color of the square, and number of the square
			System.out.printf("Spun %d...Iron is now sitting on %s square #%d\n",numRolled,this.squares[position],position);
		}
	}
}
