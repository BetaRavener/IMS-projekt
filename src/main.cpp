#include <iostream>
#include <simlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include <chrono>
#include "generator.h"
#include "globals.h"

#include "model.h"
#include "experiment.h"

using namespace std;

Model model;
int yearNum = 0;

Histogram internationalHist("international transport", 0, YEAR / YEAR_HIST_SCALE, YEARS_SIMULATION);
Histogram importHist("import",0, YEAR / YEAR_HIST_SCALE, YEARS_SIMULATION);
Histogram exportHist("export",0, YEAR / YEAR_HIST_SCALE, YEARS_SIMULATION);
Histogram nationalHist("national transport", 0, YEAR / YEAR_HIST_SCALE, YEARS_SIMULATION);


int main()
{
    // Initialize components not related to model
    // ...


    // Initialize simlib model and related components
    // Set time in which to begin and end simulation

    // Use more precise time with c++11
    //time_t seed = time(NULL);
    unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
    RandomSeed(seed);
    Init(0, YEAR*YEARS_SIMULATION);
    (new Generator(6298000, new vector <Place*> {model.labe}, new vector <Place*> {model.dunaj}, &internationalHist))->Activate();
    (new Generator(4925000, new vector <Place*> {model.dunaj}, new vector <Place*> {model.labe}, &internationalHist))->Activate();
    (new Generator(8919000, new vector <Place*> {model.odra}, new vector <Place*> {model.dunaj}, &internationalHist))->Activate();
    (new Generator(5833000, new vector <Place*> {model.dunaj}, new vector <Place*> {model.odra}, &internationalHist))->Activate();

    // import to all czech ports
    (new Generator(265000, new vector <Place*> {model.labe}, new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov}, &importHist))->Activate();
    // there is elbe, due to ports in czech that are not included in our model, therefore destination is elbe as exit point
    (new Generator(2161000, new vector <Place*> {model.dunaj}, new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov, model.labe}, &importHist))->Activate();
    (new Generator(903000, new vector <Place*> {model.odra}, new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov, model.labe}, &importHist))->Activate();

    // export from czech republic
    // goods that all ports may export
    (new Generator(1514000, new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov, model.labe}, new vector <Place*> {model.dunaj}, &exportHist))->Activate();
    (new Generator(692500, new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov, model.labe}, new vector <Place*> {model.odra}, &exportHist))->Activate();
    (new Generator(316500, new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov}, new vector <Place*> {model.labe}, &exportHist))->Activate();


    // bohnice export (ores, fuels, metals, see doc)
    // danube
    (new Generator(3173000, new vector <Place*> {model.bohumin}, new vector <Place*> {model.dunaj}, &exportHist))->Activate();
    // elbe
    (new Generator(35000, new vector <Place*> {model.bohumin}, new vector <Place*> {model.labe}, &exportHist))->Activate();
    // oder
    (new Generator(135000, new vector <Place*> {model.bohumin}, new vector <Place*> {model.odra}, &exportHist))->Activate();


    // labe(ports from czech but beyond our map), pardubice export (oil, chemistry products, oil products...mainly chemistry industry, see doc)
    // danube
    (new Generator(442000, new vector <Place*> {model.labe, model.pardubice}, new vector <Place*> {model.dunaj}, &exportHist))->Activate();
    // oder
    (new Generator(53000, new vector <Place*> {model.labe, model.pardubice}, new vector <Place*> {model.odra}, &exportHist))->Activate();
    // labe, now considering only pardubice
    (new Generator(12000, new vector <Place*> {model.pardubice}, new vector <Place*> {model.labe}, &exportHist))->Activate();


    // national transport
    (new Generator(2150000,
            new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov, model.labe},
            new vector <Place*> {model.brodske, model.pardubice, model.bohumin, model.hodonin, model.prerov, model.prerov},
            &nationalHist))->Activate();

    // Run simulation
    Run();


    internationalHist.Output();
    importHist.Output();
    exportHist.Output();
    nationalHist.Output();

    Experiment::instance()->minShipsCalculate();
    Experiment::instance()->Output();

    // Display results and perform cleanup if necessary
    return 0;
}
