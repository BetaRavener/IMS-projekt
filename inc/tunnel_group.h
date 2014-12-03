/*
 * tunnel_group.h
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#ifndef TUNNEL_GROUP_H_
#define TUNNEL_GROUP_H_

#include <simlib.h>
#include "place.h"

class TunnelGroup : public Process
{
public:
    TunnelGroup(Facility &tunnel);

    void joinGroup();

    void leaveGroup();

    bool empty();

    bool full();

    Direction getDirection();

    int getTotalSize();

private:
    int totalSize;
    int currentSize;
    Facility &tunnel;

    void Behavior();
};


#endif /* TUNNEL_GROUP_H_ */
