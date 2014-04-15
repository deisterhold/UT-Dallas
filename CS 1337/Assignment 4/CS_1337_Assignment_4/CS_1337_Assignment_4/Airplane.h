//
//  Airplane.h
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS_1337_Assignment_4__Airplane__
#define __CS_1337_Assignment_4__Airplane__

#include "Aircraft.h"

#include <iostream>

class Airplane : public Aircraft
{
public:
    //Constructor and Destructor
    Airplane();
    Airplane(uint, uint, bool);
    ~Airplane();
    
    //Setter and getter for wing width
    uint getWingWidth() const;
    void setWingWidth(uint);
    
    //Setter and getter for elevator width
    uint getElevatorWidth() const;
    void setElevatorWidth(uint);
    
    //Setter and getter for rudder height
    uint getRudderHeight() const;
    void setRudderHeight(uint);
    
    //Setter and getter for aileron angle
    uint getMaxAileronAngle() const;
    void setMaxAileronAngle(uint);
    
    //Setter and getter for elevator angle
    uint getMaxElevatorAngle() const;
    void setMaxElevatorAngle(uint);
    
    //Setter and getter for rudder angle
    uint getMaxRudderAngle() const;
    void setMaxRudderAngle(uint);
    
    //Setter and getter for propeller diameter
    uint getPropellerDiameter() const;
    void setPropellerDiameter(uint);
    
    //Setter and getter for flap length
    uint getMaxFlapLength() const;
    void setMaxFlapLength(uint);
    
    //Setter and getter for is a jet
    bool getIsAJet() const;
    void setIsAJet(bool);
    
    //Prints characteristics of the airplane
    virtual void printCharacteristics() const;
    
private:
    uint wingWidth;
    uint elevatorWidth;
    uint rudderHeight;
    uint maxAileronAngle;
    uint maxElevatorAngle;
    uint maxRudderAngle;
    uint propellerDiameter;
    uint maxFlapLength;
    bool isAJet;
};

#endif /* defined(__CS_1337_Assignment_4__Airplane__) */
