//
//  Rocket.h
//  CS_1337_Assignment_4
//
//  Created by Daniel Eisterhold on 3/23/14.
//  Copyright (c) 2014 Daniel Eisterhold. All rights reserved.
//

#ifndef __CS_1337_Assignment_4__Rocket__
#define __CS_1337_Assignment_4__Rocket__

#include "Aircraft.h"

#include <iostream>

class Rocket: public Aircraft
{
public:
    //Constructor and Destructor
    Rocket();
    Rocket(uint , uint);
    ~Rocket();
    
    //Setter and getter for rocket thrust
    uint getTotalThrust() const;
    void setTotalThrust(uint);
    
    //Setter and getter for rocket height
    uint getRocketHeight() const;
    void setRocketHeight(uint);
    
    //Setter and getter for center of mass
    uint getCenterOfMass() const;
    void setCenterOfMass(uint);
    
    //Setter and getter for center of gravity
    uint getCenterOfGravity() const;
    void setCenterOfGravity(uint);
    
    //Setter and getter for number of fins
    uint getNumberOfFins() const;
    void setNumberOfFins(uint);
    
    //Setter and getter for number of parachutes
    uint getNumberOfParachutes() const;
    void setNumberOfParachutes(uint);
    
    //Setter and getter for is guided
    bool getIsGuided() const;
    void setIsGuided(bool);
    
    //Setter and getter for is gimbaled
    bool getIsGimbaled() const;
    void setIsGimbaled(bool);
    
    //Prints characteristics of the rocket
    virtual void printCharacteristics() const;
    
private:
    uint totalThrust;
    uint rocketHeight;
    uint centerOfMass;
    uint centerOfGravity;
    uint numberOfFins;
    uint numberOfParachutes;
    bool isGuided;
    bool isGimbaled;
};

#endif /* defined(__CS_1337_Assignment_4__Rocket__) */
