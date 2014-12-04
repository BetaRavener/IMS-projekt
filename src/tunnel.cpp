/*
 * tunnel.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#include "tunnel.h"

#define MAX_TUNNEL_SPEED (9.28 / 3.6) // in meters / second

Tunnel::Tunnel(const char* name, double length, unsigned int minGroupSize) :
    Place(name),
    queueA("queueA"),
    queueB("queueB"),
    wholeTunnel(name),
    length(length),
    minGroupSize(minGroupSize),
    groupSize("Tunnel group size"),
    group(nullptr)
{}

void Tunnel::SailProcedure(Ship &ship)
{
    Direction direction = ship.getSailDirection();
    Queue &myQueue = direction == Direction::ToEndpoint ? queueA : queueB;
    Queue &oppositeQueue = direction == Direction::ToEndpoint ? queueB : queueA;

    // If tunnel is already used, queue up
    if (wholeTunnel.Busy())
    {
        ship.Into(myQueue);
        ship.Passivate();
    }

    // Create new tunnel group if this is first ship
    if (group == nullptr)
    {
        group = new TunnelGroup(wholeTunnel);
        group->Activate();
    }

    group->joinGroup();

    // If group is not full, activate next ship waiting in same direction
    if (!group->full() && !myQueue.Empty())
    {
        // Time needed for ship to fully enter tunnel
        static_cast<Ship*>(myQueue.GetFirst())->Activate(Time + ship.getLength() / MAX_TUNNEL_SPEED);
    }

    // Start sailing through tunnel
    ship.Sail(length, MAX_TUNNEL_SPEED);

    group->leaveGroup();

    // Signal that tunnel is free if this was last ship in group
    if (group->empty())
    {
        // The queue in opposite direction has priority
        // If both queues were empty leave tunnel free
        if (!oppositeQueue.Empty())
            oppositeQueue.GetFirst()->Activate();
        else if (!myQueue.Empty())
            myQueue.GetFirst()->Activate();

        groupSize(group->getTotalSize());
        group->Activate();
        group = nullptr;
    }
}

void Tunnel::Output()
{
    wholeTunnel.Output();
    groupSize.Output();
    queueA.Output();
    queueB.Output();
}
