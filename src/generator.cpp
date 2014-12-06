/*
 * generator.cpp
 *
 *  Created on: 4.12.2014
 *      Author: ivan_hoe
 */

#include "generator.h"
#include "ship.h"

Generator::Generator(double avgTons, std::vector <Place*>  *src, std::vector <Place*> *dest, Histogram *hist):
    avgTons(avgTons),
    tonsLeft(avgTons),
    nextShipTime(YEAR /  (avgTons / SHIP_CAPACITY)),
    srcV(src),
    destV(dest),
    actualYear(0),
    hist(hist)
    {}


Generator::~Generator() {
    delete srcV;
    srcV = nullptr;
    delete destV;
    destV = nullptr;
}

void Generator::Behavior(){

    Place* src = getUniformPlace(srcV);
    Place* dest= getUniformPlace(destV, src);

    // get year in actual time
    int year = (int)(Time / YEAR);

    while (actualYear < year)
    {
        // increase tons by 2% by every year
        this->avgTons *= 1.02;
        this->tonsLeft = avgTons;
        this-> nextShipTime = YEAR /  (this->tonsLeft / SHIP_CAPACITY);
        actualYear++;
    }
    double tons = (tonsLeft > SHIP_CAPACITY)? SHIP_CAPACITY:tonsLeft;
    tonsLeft -= tons;
    (new Ship(src, dest, false, tons))->Activate();
    if (hist)
       (*hist)(Time / YEAR_HIST_SCALE);
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

