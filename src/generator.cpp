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
    nextShipTime((YEAR - DAY*10) /  (avgTons / SHIP_CAPACITY)),
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
    int day = (((int) (Time / DAY))*100 % 36525) / 100;
    if (!(0 <= day && day < 10))
    {
		while (actualYear < year)
		{
			// increase tons by 2% by every year
			this->avgTons *= 1.02;
			this-> nextShipTime = (YEAR - DAY*10) /  (this->avgTons / SHIP_CAPACITY);
			actualYear++;
		}
		(new Ship(src, dest, false, 4000))->Activate();
		if (hist)
		   (*hist)(Time / YEAR_HIST_SCALE);
    }
    //else
    //	Print("%f %d\n",Time, day);
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

