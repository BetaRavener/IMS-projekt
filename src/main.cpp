#include <iostream>
#include <simlib.h>
#include <time.h>

#include "model.h"

Model model;

class Generator : public Event {
  void Behavior() {
    model.addShip();
    Activate(Time+Exponential(1000));
  }
};

int main()
{
    // Initialize components not related to model
    // ...
    //TODO: use more precise time with c++11
    time_t seed = time(NULL);

    // Initialize simlib model and related components
    // Set time in which to begin and end simulation
    RandomSeed(seed);
    Init(0, 1000000);
    (new Generator)->Activate();

    // Run simulation
    Run();

    model.Output();

    // Display results and perform cleanup if necessary
    return 0;
}
