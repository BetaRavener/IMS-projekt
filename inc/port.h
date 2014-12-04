/*
 * port.h
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#ifndef PORT_H_
#define PORT_H_

#include <simlib.h>
#include "place.h"
#include "ship.h"

class Port : public Place
{
public:
    Port(const char* name, int quayCapacity = 50, double transferSpeed = 0.05);

    virtual void SailProcedure(Ship &s);

    virtual void Output();

private:
    Store quay;
    double transferSpeed;
};

#endif /* PORT_H_ */
