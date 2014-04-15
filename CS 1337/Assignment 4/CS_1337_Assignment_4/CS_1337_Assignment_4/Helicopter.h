//
//  Helicopter.h
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS_1337_Assignment_4__Helicopter__
#define __CS_1337_Assignment_4__Helicopter__

//Add Classes
#include "Aircraft.h"

#include <iostream>

class Helicopter: public Aircraft
{
public:
    //Constructor and Destructor
    Helicopter();
    Helicopter(uint, uint);
    ~Helicopter();
    
    //Setter and getter for number of blades
    uint getNumberOfBladesPerRotor() const;
    void setNumberOfBladesPerRotor(uint);
    
    //Setter and getter for number of rotors
    uint getNumberOfRotors() const;
    void setNumberOfRotors(uint);
    
    //Setter and getter for number of wheels
    uint getNumberOfWheels() const;
    void setNumberOfWheels(uint);
    
    //Setter and getter for can land on water
    bool getCanLandOnWater() const;
    void setCanLandOnWater(bool);
    
    //Setter and getter for has skids
    bool getHasSkids() const;
    void setHasSkids(bool);
    
    //Prints characteristics of the helicopter
    virtual void printCharacteristics() const;
    
private:
    uint numberOfBladesPerRotor;
    uint numberOfRotors;
    uint numberOfWheels;
    bool canLandOnWater;
    bool hasSkids;
};

#endif /* defined(__CS_1337_Assignment_4__Helicopter__) */
