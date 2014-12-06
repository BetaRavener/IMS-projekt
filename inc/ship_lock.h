/*
 * ship_lock.h
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#ifndef SHIP_LOCK_H_
#define SHIP_LOCK_H_

#include <vector>
#include <string>
#include <simlib.h>
#include "place.h"
#include "tunnel_group.h"
#include "ship.h"

class ShipLock : public Place
{
public:
    ShipLock(const char* name, double height, Direction riseDirection, int chamberCount = 2);

    virtual void SailProcedure(Ship &s);

    virtual void Output();

private:
    enum class ChamberLevel {Low, High};

    std::vector<Queue*> queueA;
    std::vector<Queue*> queueB;
    std::vector<Facility*> shipLock;
    std::vector<ChamberLevel> chamberLevel;
    std::vector<std::string> names;

    double chamberWaitTime;
    Direction riseDirection;

    void toggleChamberLevel(int idx);
    bool isLevelInDirection(Direction direction, int idx);
    int chooseChamber(Direction direction);
};

#endif /* SHIP_LOCK_H_ */
