/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package Dallopoly;

import Squares.Square;

public class Player {
	//Variables to hold name of player and the spot that the player is at
	private String name;
	private Square currentSquare;
	private int money;
	
	//Constructor that accepts name and starting square
	public Player(String _name, Square _square) {
		//Initialize the variables
		this.setName(_name);
		this.setCurrentSquare(_square);
		System.out.println(this.toString());
	}
	
	//Returns player name
	public String getName() {
		return this.name;
	}
	
	//Sets the players name
	public void setName(String _name) {
		this.name = _name;
	}

	//Set the amount of money the player has
	public void setMoney(int moneyAmount) {
		this.money = moneyAmount;
	}
	
	//Get the amount of money the player has
	public int getMoney() {
		return this.money;
	}
	
	//Increases or decreases players money
	public void changeMoney(int changeAmount) {
		this.money += changeAmount;
	}
	
	//Returns square player is currently on
 	public Square getCurrentSquare() {
		return this.currentSquare;
	}
	
	//Sets the square the player is on
	public void setCurrentSquare(Square _currentSquare) {
		this.currentSquare = _currentSquare;
	}
	
	//Player spins then moves to that spot if it exists
	public void takeTurn(Spinner theSpinner, Board gameBoard) {
		//Spin the spinner to get the number of spots to move
		int spotsToMove = theSpinner.spin();
		
		//Get the new square that the player is at after move a number of spots
		Square newSquare = gameBoard.move(this.getCurrentSquare(), spotsToMove);
		
		//Sets the players square to the new spot
		this.setCurrentSquare(newSquare);
		
		//Notify the square you landed on it to either receive or lose $
		this.getCurrentSquare().landOn(this);
		
		//Output what the player spun and new position
		System.out.println(this.getName() + " spun " + spotsToMove + " " + this.toString());
	}
	
	//Returns info about the player
	public String toString() {
		//Creates string containing the name of the player and the spot they are at
		String data = this.getName() + " has $" + this.getMoney() + " is on " + this.getCurrentSquare().getLabel() + " square";
		return data;
	}
}
