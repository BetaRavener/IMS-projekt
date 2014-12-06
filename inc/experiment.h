/*
 * experiment.h
 *
 *  Created on: Dec 4, 2014
 *      Author: raven
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include <simlib.h>
#include <math.h>
#include "globals.h"

class Experiment
{
public:
    static Experiment* instance();

    void addRoute(double length, double time);
    void addToll(double sectionLength, double cargoSize, double tollRate = 0.01);

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
    // income
    double income;

    // time whe investments are payed back
    double payedBackTime;
};

#endif /* EXPERIMENT_H_ */
