//
//  Aircraft.h
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS_1337_Assignment_4__Aircraft__
#define __CS_1337_Assignment_4__Aircraft__

#include <iostream>
#include <string>

using namespace std;

class Aircraft
{
public:
    //Constructor and Destructor
    Aircraft();
    Aircraft(uint,uint,uint);
    ~Aircraft();
    
    //Setter and getter for engines
    uint getNumberOfEngines() const;
    void setNumberOfEngines(uint);
    
    //Setter and getter for pilots
    uint getNumberOfPilots() const;
    void setNumberOfPilots(uint);
    
    //Setter and getter for passengers
    uint getNumberOfPassengers() const;
    void setNumberOfPassengers(uint);
    
    //Setter and getter for manufacturer
    string getAircraftManufacturer() const;
    void setAircraftManufacturer(string);
    
    //Setter and getter for payload
    uint getPayloadCapacity() const;
    void setPayloadCapacity(uint);
    
    //Setter and getter for range
    uint getAircraftRange() const;
    void setAircraftRange(uint);
    
    //Setter and getter for max speed
    uint getMaximumSpeed() const;
    void setMaximumSpeed(uint);
    
    //Setter and getter for VTOL (Vertical Takeoff and Landing)
    bool getVTOL() const;
    void setVTOL(bool);
    
    //Prints characteristics of the aircraft
    virtual void printCharacteristics() const;
    
private:
    uint numberOfEngines;
    uint numberOfPilots;
    uint numberOfPassengers;
    string aircraftManufacturer;
    uint payloadCapacity;
    uint aircraftRange;
    uint maximumSpeed;
    bool vtol;
};

#endif /* defined(__CS_1337_Assignment_4__Aircraft__) */
