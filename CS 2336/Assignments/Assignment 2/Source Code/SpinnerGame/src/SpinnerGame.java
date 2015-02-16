/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.util.*;

class SpinnerGame {
    //Player names
    String playerOneName;
    String playerTwoName;
    //Player scores
    int playerOneScore;
    int playerTwoScore;
    //Random number generator
    Random randNum = new Random();
    
    public SpinnerGame() {
    	this("Player 1", "Player 2"); //Set players names
    }
    
    public SpinnerGame(String name1, String name2) {
    	//Set names
    	playerOneName = name1;
    	playerTwoName = name2;
    	//Set scores to 0
    	playerOneScore = 0;
        playerTwoScore = 0;
        //Set random number generator seed to system time
        randNum.setSeed(System.currentTimeMillis());
    }
    
    public void playerOneSpin() {
    	//Output what player one spun and current score
    	System.out.print(playerOneName + " ");
    	playerOneScore += spin();
    	System.out.println(" and now has a score of " + this.playerOneScore);
    }
    
    public void playerTwoSpin() {
    	//Output what player two spun and current score
    	System.out.print(playerTwoName + " ");
    	playerTwoScore += spin();
    	System.out.println(" and now has a score of " + this.playerTwoScore);
    }
    
    private int spin() {
    	final int[] wheelValues = {5,3,2,1,-1,-2,-3,-5};
    	int score =  wheelValues[randNum.nextInt(8)]; //Get random score from wheel
    	System.out.print("spun " + score); //Output what was spun
    	return score; //Return value
    }
    
    public boolean isOver() { //Check if either player has a score greater than 10
    	if((this.playerOneScore > 10) || (this.playerTwoScore > 10)) return true;
    	else return false;
    }
    
    //Output winner takes both players scores
    public void displayWinner(int player1Score, int player2Score) {
    	if(player1Score > player2Score) { //If player one has a greater score
    		System.out.println(this.playerOneName + " Won!!"); //Output player one won
    	}
    	else if(player1Score < player2Score) { //If player two has a greater score
    		System.out.println(this.playerTwoName + " Won!!"); //Output player two won
    	}
    	else { //Otherwise
    		System.out.println("Tie"); //Output it was a tie
    	}
    	
    }
    
    public static void main(String[] args) {
        SpinnerGame myGame = new SpinnerGame(); //Create SpinnerGame object
        while(!myGame.isOver()) { //Loop until game is over
        	myGame.playerOneSpin(); //Spin for player one
        	myGame.playerTwoSpin(); //Spin for player two
        }
        //After game is over display the winner
        myGame.displayWinner(myGame.playerOneScore, myGame.playerTwoScore);
    }

}


