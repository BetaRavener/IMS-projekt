/*
 * port.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#include "port.h"

Port::Port(const char* name, int quayCapacity, double transferSpeed) :
    Place(name),
    quay(name, quayCapacity),
    transferSpeed(transferSpeed)
{}

void Port::SailProcedure(Ship &s)
{
    // If this is ships destination, proceed with procedure.
    // Otherwise the ship is just passing the port
    if (s.getDestination() == this)
    {
        s.Enter(quay, 1);
        s.Wait((double)s.getCargoSize() / transferSpeed);
        s.Leave(quay, 1);
    }
}

void Port::Output()
{
    quay.Output();
}
