/*
 * experiment.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: raven
 */

#include "experiment.h"

Experiment* Experiment::experiment = nullptr;

Experiment* Experiment::instance()
{
    if (experiment == nullptr)
        experiment = new Experiment();

    return experiment;
}

void Experiment::addRoute(double length, double time)
{
    routeLength(length);
    routeTime(time);
}

void Experiment::addToll(double sectionLength, double cargoSize, double tollRate)
{
	double shipToll = sectionLength * cargoSize * tollRate;
    toll(shipToll);

    // project has been payed back
    if (payedBackTime != -1)
    	return;
    // add total income. If investments are payed back, Time will be written down.
    // investments are increased by maintenance costs. Those are added per year quarter.
    if (income < investments + ((long) Time / (YEAR_QUARTER)) * yearQuarterCosts)
    {
    	income += shipToll;
    }
    //
    if (income >= investments + ((long) Time / (YEAR_QUARTER)) * yearQuarterCosts)
    {
    	payedBackTime = Time;
    }
}

void Experiment::Output()
{
    routeLength.Output();
    Print("Total: %f\n", routeLength.Sum());
    routeTime.Output();
    Print("Total: %f\n", routeTime.Sum());
    toll.Output();
    Print("Total: %f\n", toll.Sum());
    if (payedBackTime != -1)
    {
    	Print("Project (%f) will be payed back in %d year and %d day\n",investments, (long) payedBackTime / (long) YEAR, ((long) payedBackTime % (int) YEAR) / DAY );
    }
    else Print("Project hasn't been payed back (%d) years\n",YEARS_SIMULATION);
}

Experiment::Experiment() :
    routeLength("Route length"),
    routeTime("Route time"),
    toll("Toll"),
    investments(8155600000.0),
    yearQuarterCosts(54800000.0 / 4),
    income(0),
    // -1 defines, that DOL hasn't been payed back, yet
    payedBackTime(-1)
{}

Experiment::Experiment(Experiment const&)
{}

Experiment& Experiment::operator=(Experiment const&)
{
    return *experiment;
}
