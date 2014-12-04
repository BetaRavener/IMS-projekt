/*
 * generator.h
 *
 *  Created on: 4.12.2014
 *      Author: ivan_hoe
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <simlib.h>
#include <vector>
#include "globals.h"
#include "place.h"

#include <iostream>
#include <string.h>


class Generator: public Event {
private:
    long avgTons;
    long tonsLeft;
    // time for exponential distribution for ships per year in seconds
    double nextShipTime;
    std::vector <Place*>  *srcV;
    std::vector <Place*>  *destV;
    long actualYear;
    Histogram *hist;
    Place* getUniformPlace(std::vector <Place*> *list, Place *except = nullptr);

public:
    Generator(long avgTons, std::vector <Place*>  *src, std::vector <Place*> *dest, Histogram *hist = nullptr);
    virtual ~Generator();
    void Behavior();
};

#endif /* GENERATOR_H_ */
