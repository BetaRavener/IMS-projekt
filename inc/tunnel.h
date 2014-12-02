/*
 * tunnel.h
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#ifndef TUNNEL_H_
#define TUNNEL_H_

#include <simlib.h>
#include "place.h"
#include "tunnel_group.h"
#include "ship.h"

class Tunnel : public Place
{
public:
    Tunnel(const char* name, double length, unsigned int minGroupSize);

    virtual void SailProcedure(Ship &s);

    virtual void Output();

private:
    Queue queueA;
    Queue queueB;
    Facility wholeTunnel;

    double length;
    unsigned int minGroupSize;

    Stat groupSize;
    TunnelGroup* group;
};

#endif /* TUNNEL_H_ */
