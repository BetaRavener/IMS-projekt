/*
 * generator.cpp
 *
 *  Created on: 4.12.2014
 *      Author: ivan_hoe
 */



#include "generator.h"


Generator::Generator(long    avgTons, std::vector <Place*>  *src, std::vector <Place*> *dest, Histogram *hist):
    srcV(src),
    avgTons(avgTons),
    tonsLeft(avgTons),
    nextShipTime(YEAR /  (avgTons / SHIP_CAPACITY)),
    actualYear(0),
    destV(dest),
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
    long year = (int)Time / YEAR;
    // increase tons by 5% by each year
    while (actualYear < year)
    {
        this->avgTons *= 1.05;
        this->tonsLeft += avgTons;
        this-> nextShipTime = YEAR /  (this->tonsLeft / SHIP_CAPACITY);
        actualYear++;

    }
    long tons = (tonsLeft > SHIP_CAPACITY)? SHIP_CAPACITY:tonsLeft;
    tonsLeft -= tons;
    //(new Ship(src, destination, false, tons))->Activate();
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

