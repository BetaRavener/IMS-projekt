/*
 * tunnel_group.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#include "tunnel_group.h"

TunnelGroup::TunnelGroup(Facility &tunnel) :
    Process(HIGHEST_PRIORITY),
    totalSize(0),
    currentSize(0),
    tunnel(tunnel)
{
}

void TunnelGroup::joinGroup()
{
    totalSize++;
    currentSize++;
}

void TunnelGroup::leaveGroup()
{
    currentSize--;
}

bool TunnelGroup::empty()
{
    return currentSize == 0;
}

bool TunnelGroup::full()
{
    return totalSize == 5;
}

int TunnelGroup::getTotalSize()
{
    return totalSize;
}

void TunnelGroup::Behavior()
{
    Seize(tunnel);
    Passivate();
    Release(tunnel);
}
