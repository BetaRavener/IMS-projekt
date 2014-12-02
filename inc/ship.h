/*
 * ship.h
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#ifndef SHIP_H_
#define SHIP_H_

#include <simlib.h>
#include "place.h"

class Ship : public Process {
public:
    Ship(Place *origin, Place *destination, double capacity = 4000, double cargoSize = 4000, double length = 180);

    Direction getSailDirection();
    void setSailDirection(Direction direction);

    double getCargoSize();
    double getLength();
    Place* getDestination();

private:
    Place *currentPlace;
    Place *destination;
    Direction sailDirection;

    double capacity; // in tons
    double cargoSize; // in tons
    double length; // in meters
    void Behavior();
};

#endif /* SHIP_H_ */
