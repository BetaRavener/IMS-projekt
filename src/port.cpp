/*
 * port.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#include "port.h"

Port::Port(const char* name, int quayCapacity, double transferSpeed) :
    quay(name, quayCapacity),
    transferSpeed(transferSpeed)
{}

void Port::SailProcedure(Ship &s)
{
    s.Enter(quay, 1);
    s.Wait((double)s.getCargoSize() / transferSpeed);
    s.Leave(quay, 1);
}

void Port::Output()
{
    quay.Output();
}
