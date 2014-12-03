/*
 * crossroad.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#include "crossroad.h"

Pathway::Pathway(Place* origin, double distance) :
    origin(origin),
    distance(distance)
{}

Crossroad::Crossroad() :
    Place("Crossroad")
{}

void Crossroad::SailProcedure(Ship &ship)
{
    Place* dest = ship.getDestination();
    Place* searched;
    for (auto x : pathways)
    {
        searched = x.origin;
        while (searched != nullptr && searched != dest)
        {
            searched = searched->getNext(Direction::ToEndpoint, nullptr);
        }

        if (searched != nullptr)
        {
            next = x.origin;
            nextDistance = x.distance;
            ship.setSailDirection(Direction::ToEndpoint);
            break;
        }
    }
}

void Crossroad::Output()
{

}

void Crossroad::connect(Place* place, double distance)
{
    Place::connect(place, distance);
    pathways.push_back(Pathway(place, distance));
    next = nullptr;
    nextDistance = 0;
}
