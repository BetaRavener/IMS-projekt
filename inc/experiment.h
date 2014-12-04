/*
 * experiment.h
 *
 *  Created on: Dec 4, 2014
 *      Author: raven
 */

#ifndef EXPERIMENT_H_
#define EXPERIMENT_H_

#include <simlib.h>

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
};

#endif /* EXPERIMENT_H_ */
