/*
 * bridge.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: raven
 */

#include "bridge.h"

#define MAX_BRIDGE_SPEED (10.19 / 3.6) // in meter / second

Bridge::Bridge(const char* name, double length, Type type) :
    Place(name),
    length(length),
    type(type),
    stat(nullptr),
    queueA(nullptr),
    queueB(nullptr),
    bridge(nullptr)
{
    if (type == Type::OneWay)
    {
        queueA = new Queue("A");
        queueB = new Queue("B");
        bridge = new Facility(name);
    }
    else
    {
        stat = new Stat(name);
    }
}

void Bridge::SailProcedure(Ship &ship)
{
    if (type == Type::TwoWay)
    {
        (*stat)(1);
        ship.Wait(length / MAX_BRIDGE_SPEED);
    }
    else
    {
        Direction direction = ship.getSailDirection();
        Queue* myQueue = direction == Direction::ToEndpoint ? queueA : queueB;
        Queue* oppositeQueue = direction == Direction::ToEndpoint ? queueB : queueA;

        // If tunnel is already used, queue up
        if (bridge->Busy())
        {
            ship.Into(*myQueue);
            ship.Passivate();
        }

        ship.Seize(*bridge);

        // Start sailing through tunnel
        ship.Sail(length, MAX_BRIDGE_SPEED);

        // Signal that tunnel is free if this was last ship in group
        // The queue in opposite direction has priority
        // If both queues were empty leave tunnel free
        if (!oppositeQueue->Empty())
            oppositeQueue->GetFirst()->Activate();
        else if (!myQueue->Empty())
            myQueue->GetFirst()->Activate();

        ship.Release(*bridge);
    }
}

void Bridge::Output()
{
    if (type == Type::OneWay)
    {
        bridge->Output();
        queueA->Output();
        queueB->Output();
    }
    else
    {
        stat->Output();
    }
}
