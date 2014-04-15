//
//  Airplane.cpp
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "Airplane.h"

//Constructor and Destructor
Airplane::Airplane()
{
    wingWidth = 0;
    elevatorWidth = 0;
    rudderHeight = 0;
    maxAileronAngle = 0;
    maxElevatorAngle = 0;
    maxRudderAngle = 0;
    propellerDiameter = 0;
    maxFlapLength = 0;
    isAJet = false;
}

Airplane::Airplane(uint wing, uint propeller, bool isJet)
{
    Airplane::Airplane();
    wingWidth = wing;
    propellerDiameter = propeller;
    isAJet = isJet;
}

Airplane::~Airplane()
{
    cout<<"A Airplane has been deleted."<<endl;
}

//Setter and getter for wing width
uint Airplane::getWingWidth() const
{
    return wingWidth;
}

void Airplane::setWingWidth(uint wing)
{
    wingWidth = wing;
}

//Setter and getter for elevator width
uint Airplane::getElevatorWidth() const
{
    return elevatorWidth;
}

void Airplane::setElevatorWidth(uint elevator)
{
    elevatorWidth = elevator;
}

//Setter and getter for rudder height
uint Airplane::getRudderHeight() const
{
    return rudderHeight;
}

void Airplane::setRudderHeight(uint rudder)
{
    rudderHeight = rudder;
}

//Setter and getter for aileron angle
uint Airplane::getMaxAileronAngle() const
{
    return maxAileronAngle;
}

void Airplane::setMaxAileronAngle(uint aileron)
{
    maxAileronAngle = aileron;
}

//Setter and getter for elevator angle
uint Airplane::getMaxElevatorAngle() const
{
    return maxElevatorAngle;
}

void Airplane::setMaxElevatorAngle(uint elevator)
{
    maxElevatorAngle = elevator;
}

//Setter and getter for rudder angle
uint Airplane::getMaxRudderAngle() const
{
    return maxRudderAngle;
}

void Airplane::setMaxRudderAngle(uint rudder)
{
    maxRudderAngle = rudder;
}

//Setter and getter for propeller diameter
uint Airplane::getPropellerDiameter() const
{
    return propellerDiameter;
}

void Airplane::setPropellerDiameter(uint propeller)
{
    propellerDiameter = propeller;
}

//Semmtter and getter for flap length
uint Airplane::getMaxFlapLength() const
{
    return maxFlapLength;
}

void Airplane::setMaxFlapLength(uint flap)
{
    maxFlapLength = flap;
}

//Setter and getter for is a jet
bool Airplane::getIsAJet() const
{
    return isAJet;
}

void Airplane::setIsAJet(bool isJet)
{
    isAJet = isJet;
}

void Airplane::printCharacteristics() const
{
    Aircraft::printCharacteristics();
    cout<<"\tThe wing width is: "<<wingWidth<<endl;
    cout<<"\tThe elevator width is: "<<elevatorWidth<<endl;
    cout<<"\tThe ruddder height is: "<<rudderHeight<<endl;
    cout<<"\tThe maximum aileron angle is: "<<maxAileronAngle<<endl;
    cout<<"\tThe maximum elevator angle is: "<<maxElevatorAngle<<endl;
    cout<<"\tThe maximum rudder angle is: "<<maxRudderAngle<<endl;
    cout<<"\tThe propeller diameter is: "<<propellerDiameter<<endl;
    cout<<"\tThe maximum flap length is: "<<maxFlapLength<<endl;
    if (isAJet)
    {
        cout<<"\tThe airplane is a jet."<<endl;
    }
    else
    {
        cout<<"\tThe airplane is not a jet."<<endl;
    }
}