/*
 Copyright (c) 2014, Daniel Eisterhold
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 
 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import java.lang.Object;

class WorldPopulation extends Object{
    //Create variables
    private double currentPop;
    private int currentYear;
    private double growthRate;
    
    public WorldPopulation()
    {
        this.currentPop = 7200000000L;
        this.currentYear = 2014;
        this.growthRate = 0.015;
    }
    
    public void printPopulation() {
        //Output the top column names
        System.out.println("Year\t\tPopulation");
        
        //Print out the current year and population
        this.printYearAndPop(this.currentYear, this.currentPop);
        
        //Calculate the population for the next 20 years
        for(int years = 0; years < 20; years++) {
            currentYear++;
            currentPop *= (1.0+this.growthRate);
            
            //Print out year and population
            this.printYearAndPop(this.currentYear, this.currentPop);
        }
    }
    
    private void printYearAndPop(int year, double pop) {
        //Output the Year and spaces
        System.out.print(year + "\t\t");
        
        //Output population with commas and 14 characters wide
        System.out.format("%,14.0f%n", pop);
    }
    
    public static void main(String[] args) {
        //Create the object
        WorldPopulation thePopulation = new WorldPopulation();
        
        //Print out the population
        thePopulation.printPopulation();
    }
}