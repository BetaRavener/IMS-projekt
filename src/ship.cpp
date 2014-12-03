/*
 * ship.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#include "ship.h"

#define EMPTY_TRAVEL_SPEED_BONUS (3.0 / 3.6) // in meter / second
#define BASE_TRAVEL_SPEED (11.0 / 3.6) // in meter / second

Ship::Ship(Place *origin, Place *destination, bool trace, double capacity, double cargoSize, double length) :
    currentPlace(origin),
    destination(destination),
    sailDirection(Direction::ToCrossroad),
    trace(trace),
    route(""),
    capacity(capacity),
    cargoSize(cargoSize),
    length(length)
{
    // Search if destination lies in the endpoint direction
    Place* searched = currentPlace;
    while (searched != nullptr)
    {
        if (searched == destination)
        {
            sailDirection = Direction::ToEndpoint;
            break;
        }
        searched = searched->getNext(Direction::ToEndpoint, nullptr);
    }
}

void Ship::Behavior()
{
    double travelDistance;
    double travelSpeed;

    if (trace)
        route += currentPlace->getName() + "\n";

    while (currentPlace != destination)
    {
        // Travel to next place
        travelSpeed = BASE_TRAVEL_SPEED + (cargoSize / capacity) * EMPTY_TRAVEL_SPEED_BONUS;
        currentPlace = currentPlace->getNext(sailDirection, &travelDistance);
        Wait(travelDistance / travelSpeed);

        if (trace)
            route += currentPlace->getName() + "\n";

        // Make action there
        currentPlace->SailProcedure(*this);
    }

    if (trace)
    {
        route += "\n";
        Print(route.c_str());
    }
}

Direction Ship::getSailDirection()
{
    return sailDirection;
}

void Ship::setSailDirection(Direction direction)
{
    sailDirection = direction;
}

double Ship::getCargoSize()
{
    return cargoSize;
}

double Ship::getLength()
{
    return length;
}

Place* Ship::getDestination()
{
    return destination;
}
