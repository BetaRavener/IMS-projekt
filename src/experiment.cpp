/*
 * experiment.cpp
 *
 *  Created on: Dec 4, 2014
 *      Author: raven
 */

#include "experiment.h"

ExperimentBottleneck::ExperimentBottleneck(Place* place) :
    firstTime(Time),
    place(place)
{}

double ExperimentBottleneck::getTime()
{
    return firstTime;
}

Place* ExperimentBottleneck::getPlace()
{
    return place;
}

Experiment* Experiment::experiment = nullptr;

Experiment* Experiment::instance()
{
    if (experiment == nullptr)
        experiment = new Experiment();

    return experiment;
}

void Experiment::addRoute(double length, double time)
{
    routeLength(length / 1000.0); // converted to km
    routeTime(time / 3600.0); // converted to hours
}

// add toll statistics for whole route
void Experiment::addRouteToll(double routeLength, double cargoSize, double tollRate)
{
    shipsToll(routeLength / 1000.0 * cargoSize * tollRate);
}

void Experiment::addToll(double sectionLength, double cargoSize, double tollRate)
{
	double shipToll = sectionLength / 1000.0 * cargoSize * tollRate;
    toll(shipToll);

    if (!payedBack)
    {
        double maintenanceCosts = (Time / YEAR_QUARTER) * yearQuarterCosts;
        // add total income. If investments are payed back, Time will be written down.
        // investments are increased by maintenance costs. Those are added per year quarter.
        if (income < investments + maintenanceCosts)
        {
            income += shipToll;
        }
        // project has been payed back
        if (income >= investments + maintenanceCosts)
        {
            payedBack = true;
            payedBackTime = Time;
        }
    }
}

void Experiment::informAboutBottleneck(Place* place)
{
    bool contains = false;
    for (unsigned int i = 0; !contains && i < bottlenecks.size(); i++)
        contains = contains || bottlenecks[i].getPlace() == place;

    if (!contains)
        bottlenecks.push_back(ExperimentBottleneck(place));
}

void Experiment::Output()
{
    routeLength.Output();
    Print("Total: %f\n", routeLength.Sum());
    routeTime.Output();
    Print("Total: %f\n", routeTime.Sum());
    toll.Output();
    Print("Total: %f\n", toll.Sum());
    if (payedBack)
    {
    	Print("Project will be payed back in %d year, %d quarter\n", (int)(payedBackTime / YEAR), (((int) (payedBackTime / YEAR_QUARTER))%4) + 1);
    }
    else
        Print("Project hasn't been payed back %d years\n", YEARS_SIMULATION);

    if (bottlenecks.size() > 1)
    {
        unsigned int count = bottlenecks.size();
        count = count > 5 ? 5 : count;

        Print("Projects has reached it's maximum capacity.\nThese are the first %d bottlenecks:\n", count);
        for (unsigned int i = 0; i < count; i++)
        {
            Print("Bottleneck %d in place %s in year %d\n", i+1, bottlenecks[i].getPlace()->getName().c_str(), (int)(bottlenecks[i].getTime() / YEAR));
            bottlenecks[i].getPlace()->Output();
        }
    }
    else
        Print("Project hasn't been reached it's maximum capacity in %d years\n", YEARS_SIMULATION);

    Print("Minimum boats per year with average toll for whole route to make project reasonable %d\n",minShips);


}

void Experiment::minShipsCalculate()
{
	minShips = (long) ceill(yearCosts / shipsToll.MeanValue());
}

Experiment::Experiment() :
    routeLength("Route length"),
    routeTime("Route time"),
    toll("Toll"),
    shipsToll("Overall ship toll"),
    investments(8155600000.0 + 195600000.0),
    yearQuarterCosts(54800000.0 / 4.0),
    yearCosts(54800000.0),
    income(0.0),
    payedBack(false),
    payedBackTime(0.0),
    minShips(0)
{}

Experiment::Experiment(Experiment const&)
{}

Experiment& Experiment::operator=(Experiment const&)
{
    return *experiment;
}
