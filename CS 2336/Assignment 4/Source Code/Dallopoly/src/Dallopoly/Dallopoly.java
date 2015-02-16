/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

package Dallopoly;

import java.util.ArrayList;

public class Dallopoly {
	//Variables to hold data about a spinner, a board
	private Spinner theSpinner;
	private Board theBoard;
	private ArrayList<Player> players;
	
	public Dallopoly() {
		//Initialize the ArrayList
		players = new ArrayList<Player>();
		
		//Initialize the Board
		this.theBoard = new Board();
		
		//Initialize the Spinner
		this.theSpinner = new Spinner();
		
		//Add both of the players to the ArrayList
		players.add(new Player("Horse", theBoard.getStartSquare()));
		players.add(new Player("Robot", theBoard.getStartSquare()));
	}
	
	public void playGame() {
		//set a flag that will change when the game ends
		boolean gameOver = false;
		
    	//Create an outer loop that exits when a player wins
    	while(gameOver == false) {
    		//Loop through the ArrayList of players and
    		//send each player the "takeTurn" message.
    		//After the player has moved, compare the player’s new square
    		//to the Board’s lastSquare. If the player is on the Board’s
    		//last square, declare that player the winner and exit the
    		//while loop.
    		
    		//Add an extra newline
    		System.out.println("");
    		for(int player = 0; player < players.size(); player++) {
    			//Have the current player take a turn
    			players.get(player).takeTurn(this.theSpinner, this.theBoard);
    			
    			//Check if the player is on the last square
    			if(players.get(player).getCurrentSquare().equals(theBoard.getLastSquare())) {
    	    		gameOver = true;
    	    		
    	    		//Output who the winner is
    	    		System.out.println("GAME OVER!!! WINNER " + players.get(player).toString().toUpperCase());
    	    		
    	    		//Exit the for loop
    	    		break;
    	    	}
    		}
    	}//end while
    }//end playGame
}
