/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//Include the random number generator
import java.util.*;

class Magic8Ball {
    //Store sayings into a string array
    static final String[] sayings =  {
				"It is certain",
				"It is decidedly so",
				"Without a doubt",
				"Yes definitely",
				"You may rely on it",
				"As I see it, yes",
				"Most likely",
				"Outlook good",
				"Yes",
				"Signs point to yes",
				"Reply hazy",
				"Ask again later",
				"Better not tell you now",
				"Cannot predict now",
				"Concentrate and ask again",
				"Don't count on it",
				"My reply is no",
				"My sources say no",
				"Outlook not so good",
				"Very doubtful",
			      };
    
    //Default Constructor
    public Magic8Ball() {
    }
    
    //Method to output a random saying
    public void answerQuestion() {
        Random randNum = new Random();
        randNum.setSeed(System.currentTimeMillis());
        System.out.println(sayings[randNum.nextInt(20)]);
    }
    
    //Method that reads the users 
    private boolean askQuestion() {
        Scanner input = new Scanner(System.in); //Create input object
        System.out.print("Ask me a question about your future: "); //Ask user for input
        String question = input.nextLine(); //Read input
        if(question.length() > 0) { //If input was not empty
            return true; //Return true
        }
        else {
            return false; //Return false
        }
    }
    
    public static void main(String[] args) {
        Magic8Ball myBall = new Magic8Ball(); //Create Magic8Ball object
        while(myBall.askQuestion()) { //While there are questions
        	myBall.answerQuestion(); //Answer questions
        }
    }

}
