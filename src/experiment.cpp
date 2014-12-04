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
    toll(sectionLength * cargoSize * tollRate);
}

void Experiment::Output()
{
    routeLength.Output();
    Print("Total: %f\n", routeLength.Sum());
    routeTime.Output();
    Print("Total: %f\n", routeTime.Sum());
    toll.Output();
    Print("Total: %f\n", toll.Sum());
}

Experiment::Experiment() :
    routeLength("Route length"),
    routeTime("Route time"),
    toll("Toll")
{}

Experiment::Experiment(Experiment const&)
{}

Experiment& Experiment::operator=(Experiment const&)
{
    return *experiment;
}
