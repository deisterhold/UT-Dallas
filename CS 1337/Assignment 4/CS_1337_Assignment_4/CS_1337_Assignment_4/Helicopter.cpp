//
//  Helicopter.cpp
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "Helicopter.h"

//Constructor and Destructor
Helicopter::Helicopter()
{
    numberOfBladesPerRotor = 0;
    numberOfRotors = 0;
    numberOfWheels = 0;
    canLandOnWater = false;
    hasSkids = true;
    Aircraft::setVTOL(true);
//    cout<<"Helicopter constructor called."<<endl;
}

Helicopter::Helicopter(uint blades, uint rotors)
{
    Helicopter();
    if (rotors > 1)
    {
        hasSkids = false;
    }
    numberOfBladesPerRotor = blades;
    numberOfRotors = rotors;
    Aircraft::setVTOL(true);
}

Helicopter::~Helicopter()
{
    cout<<"A Helicopter has been deleted"<<endl;
}

//Setter and getter for number of blades
uint Helicopter::getNumberOfBladesPerRotor() const
{
    return numberOfBladesPerRotor;
}

void Helicopter::setNumberOfBladesPerRotor(uint blades)
{
    numberOfBladesPerRotor = blades;
}

//Setter and getter for number of rotors
uint Helicopter::getNumberOfRotors() const
{
    return numberOfRotors;
}

void Helicopter::setNumberOfRotors(uint rotors)
{
    numberOfRotors = rotors;
}

//Setter and getter for number of wheels
uint Helicopter::getNumberOfWheels() const
{
    return numberOfWheels;
}

void Helicopter::setNumberOfWheels(uint wheels)
{
    numberOfWheels = wheels;
}

//Setter and getter for can land on water
bool Helicopter::getCanLandOnWater() const
{
    return canLandOnWater;
}

void Helicopter::setCanLandOnWater(bool onWater)
{
    canLandOnWater = onWater;
}

//Setter and getter for has skids
bool Helicopter::getHasSkids() const
{
    return hasSkids;
}

void Helicopter::setHasSkids(bool skids)
{
    hasSkids = skids;
}

void Helicopter::printCharacteristics() const
{
    Aircraft::printCharacteristics();
    cout<<"\tThe helicopter has: "<<numberOfBladesPerRotor<<" blades per rotor."<<endl;
    cout<<"\tThe helicopter has: "<<numberOfRotors<<" rotors."<<endl;
    cout<<"\tThe helicopter has: "<<numberOfWheels<<" wheels."<<endl;
    if (canLandOnWater)
    {
        cout<<"\tThe helicopter can land on water."<<endl;
    }
    else
    {
        cout<<"\tThe helicopter can not land on water."<<endl;
    }
    if (hasSkids)
    {
        cout<<"\tThe helicopter has a pair of skids."<<endl;
    }
    else
    {
        cout<<"\tThe helicopter does not have a pair of skids."<<endl;
    }
    
}