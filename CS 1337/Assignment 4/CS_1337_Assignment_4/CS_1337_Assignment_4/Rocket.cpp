//
//  Rocket.cpp
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "Rocket.h"

//Constructor and Destructor
Rocket::Rocket()
{
    totalThrust = 0;
    rocketHeight = 0;
    centerOfMass = 0;
    centerOfGravity = 0;
    numberOfFins = 0;
    numberOfParachutes = 0;
    isGuided = false;
    isGimbaled = false;
    setVTOL(true);
}

Rocket::Rocket(uint height, uint fins)
{
    Rocket::Rocket();
    rocketHeight = height;
    centerOfGravity = height/2;
    centerOfMass = height/2;
    numberOfFins = fins;
}

Rocket::~Rocket()
{
    cout<<"A Rocket has been deleted."<<endl;
}

//Setter and getter for rocket thrust
uint Rocket::getTotalThrust() const
{
    return totalThrust;
}

void Rocket::setTotalThrust(uint thrust)
{
    totalThrust = thrust;
}

//Setter and getter for rocket height
uint Rocket::getRocketHeight() const
{
    return rocketHeight;
}

void Rocket::setRocketHeight(uint height)
{
    rocketHeight = height;
}

//Setter and getter for center of mass
uint Rocket::getCenterOfMass() const
{
    return centerOfMass;
}

void Rocket::setCenterOfMass(uint mass)
{
    centerOfMass = mass;
}

//Setter and getter for center of gravity
uint Rocket::getCenterOfGravity() const
{
    return centerOfGravity;
}

void Rocket::setCenterOfGravity(uint gravity)
{
    centerOfGravity = gravity;
}

//Setter and getter for number of fins
uint Rocket::getNumberOfFins() const
{
    return numberOfFins;
}

void Rocket::setNumberOfFins(uint fins)
{
    numberOfFins = fins;
}

//Setter and getter for number of parachutes
uint Rocket::getNumberOfParachutes() const
{
    return numberOfParachutes;
}

void Rocket::setNumberOfParachutes(uint parachute)
{
    numberOfParachutes = parachute;
}

//Setter and getter for is guided
bool Rocket::getIsGuided() const
{
    return isGuided;
}

void Rocket::setIsGuided(bool guided)
{
    isGuided = guided;
}

//Setter and getter for is gimbaled
bool Rocket::getIsGimbaled() const
{
    return isGimbaled;
}

void Rocket::setIsGimbaled(bool gimbaled)
{
    isGimbaled = gimbaled;
}

 void Rocket::printCharacteristics() const
{
    Aircraft::printCharacteristics();
    cout<<"\tThe Rockets total thrust is: "<<totalThrust<<endl;
    cout<<"\tThe height of the rocket is: "<<rocketHeight<<endl;
    cout<<"\tThe center of mass is at: "<<centerOfMass<<endl;
    cout<<"\tThe center of gravity is at: "<<centerOfGravity<<endl;
    cout<<"\tThe rocket has "<<numberOfFins<<" fins."<<endl;
    cout<<"\tThe rocket has "<<numberOfParachutes<<" parachutes."<<endl;
    if(isGuided)
    {
        cout<<"\tThe rocket is guided."<<endl;
    }
    else
    {
        cout<<"\tThe rocket is not guided."<<endl;
    }
    if(isGimbaled)
    {
        cout<<"\tThe rocket is gimbaled."<<endl;
    }
    else
    {
        cout<<"\tThe rocket is not gimbaled."<<endl;
    }
}