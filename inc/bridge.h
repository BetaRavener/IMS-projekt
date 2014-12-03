/*
 * bridge.h
 *
 *  Created on: Dec 3, 2014
 *      Author: raven
 */

#ifndef BRIDGE_H_
#define BRIDGE_H_

#include <simlib.h>
#include "place.h"
#include "ship.h"

class Bridge : public Place
{
public:
    enum class Type {OneWay, TwoWay};

    Bridge(const char* name, double length, Type type);

    virtual void SailProcedure(Ship &ship);

    virtual void Output();

private:
    double length;
    Type type;

    Stat* stat;
    Queue* queueA;
    Queue* queueB;
    Facility* bridge;
};

#endif /* BRIDGE_H_ */
