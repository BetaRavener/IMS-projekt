/*
 * experiment.h
 *
 *  Created on: Dec 4, 2014
 *      Author: raven
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include <simlib.h>
#include <vector>
#include <math.h>
#include "globals.h"
#include "place.h"

class ExperimentBottleneck
{
public:
    ExperimentBottleneck(Place* place);

    double getTime();
    Place* getPlace();

private:
    double firstTime;
    Place* place;
};

class Experiment
{
public:
    static Experiment* instance();

    void addRoute(double length, double time);
    void addToll(double sectionLength, double cargoSize, double tollRate = 0.01);
    void informAboutBottleneck(Place* place);
    void minShipsCalculate();

    void Output();
private:
    // Make constructors private
    Experiment();
    Experiment(Experiment const&);
    Experiment& operator=(Experiment const&);

    // Singleton
    static Experiment* experiment;

    // Experiment statistics
    Stat routeLength;
    Stat routeTime;
    Stat toll;

    // Approximate investments
    double investments;
    double yearQuarterCosts;
    double yearCosts;
    // income
    double income;

    // time whe investments are payed back
    bool payedBack;
    double payedBackTime;

    // minimum ships per year to be rentabile
    long minShips;

    // route bottlenecks
    std::vector<ExperimentBottleneck> bottlenecks;
};

#endif /* EXPERIMENT_H_ */
