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
    Ship(Place *origin, Place *destination, bool trace = false, double capacity = 4000, double cargoSize = 4000, double length = 180);

    Direction getSailDirection();
    void setSailDirection(Direction direction);

    double getCargoSize();
    double getLength();
    Place* getDestination();

private:
    Place *currentPlace;
    Place *destination;
    Direction sailDirection;

    bool trace;
    std::string route;

    double capacity; // in tons
    double cargoSize; // in tons
    double length; // in meters

    void Behavior();
};

#endif /* SHIP_H_ */
