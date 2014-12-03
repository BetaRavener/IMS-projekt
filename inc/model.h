/*
 * model.h
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "port.h"
#include "ship_lock.h"
#include "tunnel_group.h"
#include "tunnel.h"
#include "ship.h"
#include "crossroad.h"

class Model
{
public:
    Model();

    void addShip();

    void Output();

private:
    Port* a;
    Port* b;
    ShipLock* lock;
    Tunnel* tunnel;

    Crossroad crossroad;
};

#endif /* MODEL_H_ */
