/*
 * model.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#include "model.h"

Model::Model()
{
    a = new Port("Bonjour", 50, 0.01);
    b = new Port("Dasvidania", 50, 0.01);
    lock = new ShipLock("Brno", 25, Direction::ToCrossroad, 3);
    tunnel = new Tunnel("Tma", 7600, 3);

    lock->connect(a, 10);
    tunnel->connect(b, 20);

    crossroad.connect(tunnel, 10);
    crossroad.connect(lock, 5);
}

void Model::addShip()
{
    (new Ship(a, b))->Activate();
}

void Model::Output()
{
    a->Output();
    b->Output();
    lock->Output();
    tunnel->Output();
}
