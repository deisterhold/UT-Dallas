//
//  Aircraft.cpp
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#include "Aircraft.h"

//Constructor and Destructor
Aircraft::Aircraft()
{
    numberOfEngines = 0;
    numberOfPilots = 0;
    numberOfPassengers = 0;
    aircraftManufacturer = "None";
    payloadCapacity = 0;
    aircraftRange = 0;
    maximumSpeed = 0;
    vtol = false;
    cout<<"Aircraft constructor called."<<endl;
}

Aircraft::Aircraft(uint pilot, uint passenger, uint payload)
{
    Aircraft::Aircraft();
    numberOfPilots = pilot;
    numberOfPassengers = passenger;
    payloadCapacity = payload;
}

Aircraft::~Aircraft()
{
    
}

//Setter and getter for engines
uint Aircraft::getNumberOfEngines() const
{
    return numberOfEngines;
}

void Aircraft::setNumberOfEngines(uint engines)
{
    numberOfEngines = engines;
}

//Setter and getter for pilots
uint Aircraft::getNumberOfPilots() const
{
    return numberOfPilots;
}

void Aircraft::setNumberOfPilots(uint pilots)
{
    numberOfPilots = pilots;
}

//Setter and getter for passengers
uint Aircraft::getNumberOfPassengers() const
{
    return numberOfPassengers;
}

void Aircraft::setNumberOfPassengers(uint passengers)
{
    numberOfPassengers = passengers;
}

//Setter and getter for manufacturer
string Aircraft::getAircraftManufacturer() const
{
    return aircraftManufacturer;
}

void Aircraft::setAircraftManufacturer(string manufacturer)
{
    aircraftManufacturer = manufacturer;
}

//Setter and getter for payload
uint Aircraft::getPayloadCapacity() const
{
    return payloadCapacity;
}

void Aircraft::setPayloadCapacity(uint payload)
{
    payloadCapacity = payload;
}

//Setter and getter for range
uint Aircraft::getAircraftRange() const
{
    return aircraftRange;
}

void Aircraft::setAircraftRange(uint range)
{
    aircraftRange = range;
}

//Setter and getter for max speed
uint Aircraft::getMaximumSpeed() const
{
    return maximumSpeed;
}

void Aircraft::setMaximumSpeed(uint speed)
{
    maximumSpeed = speed;
}

//Setter and getter for VTOL (Vertical Takeoff and Landing)
bool Aircraft::getVTOL() const
{
    return vtol;
}

void Aircraft::setVTOL(bool verticalTakeOff)
{
    vtol = verticalTakeOff;
}

//Prints characteristics of the aircraft
void Aircraft::printCharacteristics() const
{
    cout<<"\tAircraft Manufacturer: "<<aircraftManufacturer<<endl;
    cout<<"\tPayload Capacity: "<<payloadCapacity<<endl;
    cout<<"\tRange of Aircraft: "<<aircraftRange<<endl;
    cout<<"\tNumber of Pilots: "<<numberOfPilots<<endl;
    cout<<"\tNumber of Engines: "<<numberOfEngines<<endl;
    cout<<"\tNumber of Passengers: "<<numberOfPassengers<<endl;
    cout<<"\tMaximum Speed of Aircraft: "<<maximumSpeed<<endl;
    
    if(vtol)
    {
        cout<<"\tThis Aircraft is able to takeoff and land vertically"<<endl;
    }
    else
    {
        cout<<"\tThis Aircraft is unable to takeoff and land vertically"<<endl;
    }
}