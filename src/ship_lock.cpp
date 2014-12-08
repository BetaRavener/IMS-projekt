/*
 * ship_lock.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#include "ship_lock.h"

// Pumping rate for low and high ship locks
#define LOW_LOCK_PUMPING_RATE 40.00 // in seconds / meter
#define HIGH_LOCK_PUMPING_RATE 25.4545 // in seconds / meter

ShipLock::ShipLock(const char* name, double height, Direction riseDirection, int chamberCount) :
    Place(name),
    riseDirection(riseDirection)
{
    for (int i = 0; i < chamberCount; i++)
    {
        shipLock.push_back(new Facility);
        queueA.push_back(new Queue);
        queueB.push_back(new Queue);
        chamberLevel.push_back(ChamberLevel::Low);
    }

    double pumpingTime = height / (height <= 12.5 ? LOW_LOCK_PUMPING_RATE : HIGH_LOCK_PUMPING_RATE);
    chamberWaitTime = 60 + pumpingTime;
}

void ShipLock::SailProcedure(Ship &s)
{
    Direction direction = s.getSailDirection();
    log(direction);

    int idx = chooseChamber(direction);
    Queue* myQueue = direction == Direction::ToEndpoint ? queueA[idx] : queueB[idx];
    Queue* oppositeQueue = direction == Direction::ToEndpoint ? queueB[idx] : queueA[idx];

    double timeout = 0.0;

    // If lock is already used or there is ship in my queue, queue up
    // If water level in chamber is wrong for this direction but lock is not used, queue up with timeout
    if (shipLock[idx]->Busy() || !isLevelInDirection(direction, idx)){
        if (shipLock[idx]->Busy() || !myQueue->Empty())
        {
            s.Into(*myQueue);
            s.Passivate();
        }
        else
        {
            s.Into(*myQueue);
            s.Wait(timeout);
        }

        // If shipLock is busy, opposite direction ship is going down (because this is first ship in opposite queue)
        // and nothing else could be using the lock. In that case just passivate further.
        if (shipLock[idx]->Busy())
        {
            s.Passivate();
            // This ship is active now, remove it from queue
            myQueue->GetFirst();
            s.Seize(*shipLock[idx]);
        }
        // If the level is still in wrong direction, there was no traffic in opposite direction
        // and level should be brought to direction of this ship.
        else if (!isLevelInDirection(direction, idx))
        {
            // This ship is active now, remove it from queue
            myQueue->GetFirst();
            s.Seize(*shipLock[idx]);
            // Time needed to bring chamber to correct level
            s.Wait(chamberWaitTime + (chamberLevel[idx] == ChamberLevel::Low ? 0 : 30));
            toggleChamberLevel(idx);
        }
        // Ship was activated by ship going in opposite direction.
        else
        {
            myQueue->GetFirst();
            s.Seize(*shipLock[idx]);
        }
    }
    // Otherwise the lock is ready to use.
    else
        s.Seize(*shipLock[idx]);

    // Top doors open while water is pumping, therefore the waiting is 0.
    // Bottom doors need 30s to open.
    double totalWaitTime = 516 + chamberWaitTime + (chamberLevel[idx] == ChamberLevel::Low ? 0 : 30) + 355;
    s.Wait(totalWaitTime);

    toggleChamberLevel(idx);

    if (!oppositeQueue->Empty())
        oppositeQueue->front()->Activate();
    else if (!myQueue->Empty())
        myQueue->front()->Activate(Time + timeout);

    s.Release(*shipLock[idx]);
}

void ShipLock::Output()
{
    Print ("Ship lock %s\n", name.c_str());
    Print ("Ships in direction ToEndpoint %ld\nShips in direction ToCrossroad %ld\n", statA, statB);
    for (unsigned int i = 0; i < shipLock.size(); i++)
    {
        Print("Statistics for chamber %d\n", i + 1);
        Print("\tUsage: %f\n", shipLock[i]->tstat.MeanValue());
        Print("\tDirection ToEndpoint queue - max %f, cur %d\n", queueA[i]->StatN.Max(), queueA[i]->size());
        Print("\tDirection ToCrossway queue - max %f, cur %d\n", queueB[i]->StatN.Max(), queueB[i]->size());
    }
}

void ShipLock::toggleChamberLevel(int idx)
{
    chamberLevel[idx] = chamberLevel[idx] == ChamberLevel::Low ? ChamberLevel::High : ChamberLevel::Low;
}

bool ShipLock::isLevelInDirection(Direction direction, int idx)
{
    bool inRiseDirection = direction == riseDirection;
    // If sailing from low to high, the level must be low and vice versa
    return chamberLevel[idx] == (inRiseDirection ? ChamberLevel::Low : ChamberLevel::High);
}

int ShipLock::chooseChamber(Direction direction)
{
    unsigned int best = 0;
    unsigned int bestIdx = 0;

    std::vector<Queue*>& myVector = direction == Direction::ToEndpoint ? queueA : queueB;

    for (unsigned int i = 0; i < shipLock.size(); i++)
    {
        if (myVector[i]->Empty())
        {
            if (!shipLock[i]->Busy())
            {
                if (isLevelInDirection(direction, i))
                    return i; // Highest priority - ready for use
                else
                {
                    if (2 > best)
                    {
                        best = 2; // Not used, but level is not right
                        bestIdx = i;
                    }
                }
            }
            else
            {
                if (isLevelInDirection(direction, i))
                {
                    if (1 > best)
                    {
                        best = 1; // Used by ship in the same direction
                        bestIdx = i;
                    }
                }
                else
                {
                    if (3 > best)
                    {
                        best = 3; // Ship is coming from opposite direction
                        bestIdx = i;
                    }
                }
            }
        }
    }

    if (best > 0)
        return bestIdx;
    else
    {
        // All queues are occupied, divide between queues evenly
        bestIdx = 0;
        best = myVector[bestIdx]->size();
        for (unsigned int i = 1; i < shipLock.size(); i++)
        {
            if (myVector[i]->size() < best)
            {
                best = myVector[i]->size();
                bestIdx = i;
            }
        }
    }
    return bestIdx;
}

void ShipLock::log(Direction incomingDirection)
{
    if (incomingDirection == Direction::ToEndpoint)
        statA += 1;
    else
        statB += 1;
}
