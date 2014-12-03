/*
 * place.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#include "place.h"

Place::Place() :
    next(nullptr),
    nextDistance(0),
    previous(nullptr),
    previousDistance(0)
{

}

Place::~Place()
{

}

void Place::connect(Place* place, double distance)
{
    next = place;
    nextDistance = distance;
    next->previous = this;
    next->previousDistance = distance;
}

Place* Place::getNext(Direction dir, double* distance)
{
    if (dir == Direction::ToCrossroad)
    {
        if (distance != nullptr)
            *distance = previousDistance;
        return previous;
    }
    else
    {
        if (distance != nullptr)
            *distance = nextDistance;
        return next;
    }
}
