#include <iostream>
#include <simlib.h>
#include <time.h>
#include <string.h>

#include "model.h"

#define DAY 86400
#define YEAR 31557600
#define SHIP_CAPACITY 4000

using namespace std;

Model model;
int yearNum = 0;

Histogram Tabulka("Tabulka",0,YEAR,4);
Histogram Tabulka2("Tabulka",0,1,7);
class GeneratorFromEnds : public Event {
    // will be incresed by years
    private:
        long avgTons;
        long tonsLeft;
    // time for exponential distribution for ships per year in seconds
        double nextShipTime;
        bool import;
        Place*  src;
        Place*  dest;
        long actualYear;

    public: GeneratorFromEnds(long avgTons, Place*  src = NULL, Place* dest = NULL, bool import = false){
        this->avgTons = this->tonsLeft = avgTons;
        this->nextShipTime = YEAR /  (avgTons / SHIP_CAPACITY);
        this->import = import;
        // dest will be used only in international mode. International is preset and not parameterized
        this->src = src;
        this->dest = dest;
        this->actualYear = 0;
    }

    public: void Behavior() {
        Place* destination = dest;
        if (import)
            switch (Uniform(0,5))
            {
                case 0:
                    destination =model.bohumin;
                    break;
                case 1:
                    destination=model.brno;
                    break;
                case 2:
                    destination=model.pardubice;
                    break;
                case 3:
                    destination=model.breclav;
                    break;
                case 4:
                    destination=model.hodonin;
                    break;
                case 5:
                    destination=model.prerov;
                    break;
            }
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
        Tabulka(Time);
        Activate(Time+Exponential(nextShipTime));
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
    Init(0, YEAR*4);
    (new GeneratorFromEnds(6298000,model.labe,model.dunaj, false))->Activate();
    (new GeneratorFromEnds(4925000,model.dunaj,model.labe, false))->Activate();
    (new GeneratorFromEnds(8919000,model.odra,model.dunaj, false))->Activate();
    (new GeneratorFromEnds(5833000,model.dunaj,model.odra, false))->Activate();

    //import to specific port
    (new GeneratorFromEnds(5833000,model.dunaj, NULL, true))->Activate();
    //(new GeneratorFromEnds(5833000,model.odra, NULL, false))->Activate();
    //(new GeneratorFromEnds(5833000,model.labe, NULL, false))->Activate();
    // Run simulation
    Run();

    Tabulka.Output();

    // Display results and perform cleanup if necessary
    return 0;
}
