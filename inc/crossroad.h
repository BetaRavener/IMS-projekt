/*
 * crossroad.h
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#ifndef CROSSROAD_H_
#define CROSSROAD_H_

#include <vector>
#include <tuple>
#include "place.h"
#include "ship.h"

struct Pathway
{
    Pathway(Place* origin, double distance);

    Place* origin;
    double distance;
};

class Crossroad : public Place
{
public:
    virtual void SailProcedure(Ship &ship);
    virtual void Output();

    virtual void connect(Place* place, double distance);

private:
    std::vector<Pathway> pathways;
};

#endif /* CROSSROAD_H_ */
