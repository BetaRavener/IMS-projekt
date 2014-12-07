/*
 * ship.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#include "ship.h"
#include "globals.h"
#include "experiment.h"

#define EMPTY_TRAVEL_SPEED_BONUS (3.0 / 3.6) // in meter / second
#define BASE_TRAVEL_SPEED (11.0 / 3.6) // in meter / second

Ship::Ship(Place *origin, Place *destination, bool trace, double capacity, double cargoSize, double length) :
    currentPlace(origin),
    destination(destination),
    sailDirection(Direction::ToCrossroad),
    trace(trace),
    route(""),
    routeLength(0),
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

// meters, meters / second
void Ship::Sail(double sectionLength, double speed)
{
    Wait(sectionLength / speed);

    // Add to route length
    routeLength += sectionLength;

    // Log toll into experiment
    Experiment::instance()->addToll(sectionLength, cargoSize);
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

void Ship::Behavior()
{
    double travelDistance;
    double travelSpeed;

    if (trace)
        route += currentPlace->getName() + "\n";

    double beginT = Time;
    while (currentPlace != destination)
    {
        // Travel to next place
        travelSpeed = BASE_TRAVEL_SPEED + (cargoSize / capacity) * EMPTY_TRAVEL_SPEED_BONUS;
        currentPlace = currentPlace->getNext(sailDirection, &travelDistance);

        Sail(travelDistance, travelSpeed);

        if (trace)
        {
            route += currentPlace->getName() + "\n";
        }

        // Make action there
        double procedureBeginT = Time;
        currentPlace->SailProcedure(*this);

        // If sailing procedure took more than one day, the system reached it's capacity and the place is bottleneck
        if (Time - procedureBeginT > (6*HOUR))
            Experiment::instance()->informAboutBottleneck(currentPlace);
    }
    double endT = Time;

    // Log route into experiment
    Experiment::instance()->addRoute(routeLength, endT - beginT);
    Experiment::instance()->addRouteToll(routeLength, cargoSize);

    if (trace)
    {
        route += "\n";
        Print(route.c_str());
    }
}
