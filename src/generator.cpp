/*
 * generator.cpp
 *
 *  Created on: 4.12.2014
 *      Author: ivan_hoe
 */

#include "generator.h"
#include "ship.h"

Generator::Generator(long avgTons, std::vector <Place*>  *src, std::vector <Place*> *dest, Histogram *hist):
    avgTons(avgTons),
    tonsLeft(avgTons),
    nextShipTime(YEAR /  (avgTons / SHIP_CAPACITY)),
    srcV(src),
    destV(dest),
    actualYear(0),
    hist(hist)
    {}


Generator::~Generator() {
    // TODO Auto-generated destructor stub
    delete srcV;
    srcV = nullptr;
    delete destV;
    destV = nullptr;
}

void Generator::Behavior(){

    Place* src = getUniformPlace(srcV);
    Place* dest= getUniformPlace(destV, src);

    // get year in actual time
    double year = trunc(Time / YEAR);
    // increase tons by 1% by every year
    // must be in cycle, due to possibility of generating next ship after more than one year (unlikely...but Murphy is bitch)
    while (actualYear < year)
    {
        this->avgTons *= 1.01;
        this->tonsLeft = avgTons;
        this-> nextShipTime = YEAR /  (this->tonsLeft / SHIP_CAPACITY);
        actualYear++;
    }
    long tons = (tonsLeft > SHIP_CAPACITY)? SHIP_CAPACITY:tonsLeft;
    tonsLeft -= tons;
    (new Ship(src, dest, false, tons))->Activate();
    if (hist)
       (*hist)(Time);
    Activate(Time+Exponential(nextShipTime));
}

Place* Generator::getUniformPlace(std::vector <Place*> *list, Place *except){
    Place *candidate;
    while(true)
    {
        candidate = (*list)[(int) Uniform(0, list->size())];
        if (candidate != except)
            return candidate;
    }
    return nullptr;
}

