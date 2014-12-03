/*
 * river_end.h
 *
 *  Created on: Dec 3, 2014
 *      Author: raven
 */

#ifndef RIVER_END_H_
#define RIVER_END_H_

#include "place.h"
#include "ship.h"

class RiverEnd : public Place
{
public:
    RiverEnd(const char* name);

    virtual void SailProcedure(Ship &s);

    virtual void Output();
private:

};

#endif /* RIVER_END_H_ */
