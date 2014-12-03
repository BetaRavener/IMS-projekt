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
#include "river_end.h"
#include "bridge.h"
#include "ship.h"
#include "crossroad.h"

class Model
{
public:
    Model();

    void addShip();

    void Output();

private:
    Place *a, *b;

    Crossroad* crossroad;

    Place* currentPathwayPlace;
    double currentRiverKm;

    Place* startPathway(Place* origin, double distanceFromCrossroad, double length = 0);
    Place* addPlaceToPathway(Place* place, double riverKm, double length = 0);
};

#endif /* MODEL_H_ */
