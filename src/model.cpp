/*
 * model.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: raven
 */

#include "model.h"

double max(double a, double b)
{
    return a > b ? a : b;
}

Model::Model()
{
    crossroad = new Crossroad();

    // Dunaj pathway
    startPathway(new ShipLock("Rokytnice", 24, Direction::ToCrossroad), 0.7);
    prerov = addPlaceToPathway(new Port("Prerov"), 2.1);
    addPlaceToPathway(new ShipLock("Zarici", 10.5, Direction::ToCrossroad), 11.5);
    addPlaceToPathway(new ShipLock("Kromeriz", 4.8, Direction::ToCrossroad), 22.2);
    addPlaceToPathway(new ShipLock("Belov", 4.5, Direction::ToCrossroad), 37.4);
    addPlaceToPathway(new ShipLock("Uh. Hradiste", 6.6, Direction::ToCrossroad), 54.2);
    addPlaceToPathway(new ShipLock("Rohatec", 11.4, Direction::ToCrossroad), 83);
    addPlaceToPathway(new ShipLock("Hodonin", 4.7, Direction::ToCrossroad), 91.9);
    hodonin = addPlaceToPathway(new Port("Hodonin"), 93.8);
    addPlaceToPathway(new ShipLock("Tvrdonice", 4.7, Direction::ToCrossroad), 109.3);
    brodske = addPlaceToPathway(new Port("Brodske"), 118.2);
    addPlaceToPathway(new Bridge("Morava", 800, Bridge::Type::TwoWay), 156.19, 800);
    addPlaceToPathway(new ShipLock("Lobau", 1.8, Direction::ToCrossroad), 188.5);
    dunaj = addPlaceToPathway(new RiverEnd("Dunaj"), 190.49);

    // Odra pathway
    startPathway(new ShipLock("Lipnik", 20.5, Direction::ToEndpoint), 20.2);
    addPlaceToPathway(new ShipLock("Cernotin", 18.5, Direction::ToEndpoint), 35.5);
    addPlaceToPathway(new ShipLock("Poruba", 11.0, Direction::ToEndpoint), 44.2);
    addPlaceToPathway(new ShipLock("Kunin", 25.0, Direction::ToCrossroad), 59.8);
    addPlaceToPathway(new Bridge("Bartosovice", 160, Bridge::Type::TwoWay), 67.18, 160);
    addPlaceToPathway(new ShipLock("Petrvald", 25.0, Direction::ToCrossroad), 75.8);
    addPlaceToPathway(new ShipLock("Ploskovice", 5.0, Direction::ToCrossroad), 80.4);
    addPlaceToPathway(new ShipLock("Vyskovice", 10.5, Direction::ToCrossroad), 83.3);
    addPlaceToPathway(new ShipLock("Svinov", 5.3, Direction::ToCrossroad), 88.6);
    addPlaceToPathway(new ShipLock("Privoz", 7.2, Direction::ToCrossroad), 94.4);
    bohumin = addPlaceToPathway(new Port("Bohumin"), 100.9);
    addPlaceToPathway(new ShipLock("Bohumin", 12.9, Direction::ToCrossroad), 109);
    odra = addPlaceToPathway(new RiverEnd("Odra"), 109.19);

    // Labe pathway
    startPathway(new ShipLock("Strelice", 24.0, Direction::ToEndpoint), 43.2);
    addPlaceToPathway(new ShipLock("Kralova", 24.0, Direction::ToEndpoint), 46.2);
    addPlaceToPathway(new Bridge("Morava", 200, Bridge::Type::TwoWay), 56.3, 200);
    addPlaceToPathway(new ShipLock("Zabreh", 13.0, Direction::ToEndpoint), 63.4);
    addPlaceToPathway(new Tunnel("Hejnice", 440, 1), 66.31, 440);
    addPlaceToPathway(new ShipLock("Hnevkov", 22.0, Direction::ToEndpoint), 67.2);
    addPlaceToPathway(new ShipLock("Homole", 22.0, Direction::ToEndpoint), 70.9);
    addPlaceToPathway(new ShipLock("Tatenice", 20.0, Direction::ToEndpoint), 76.6);
    addPlaceToPathway(new Tunnel("Vrcholovy", 7600, 3), 89.63, 7600);
    addPlaceToPathway(new Bridge("Usti", 1200, Bridge::Type::TwoWay), 103.25, 1200);
    addPlaceToPathway(new ShipLock("Kerhartice", 27.5, Direction::ToCrossroad), 105);
    addPlaceToPathway(new Tunnel("Roven", 500, 1), 110.43, 500);
    addPlaceToPathway(new Bridge("Roven", 200, Bridge::Type::TwoWay), 110.93, 200);
    addPlaceToPathway(new ShipLock("Brandys", 22.5, Direction::ToCrossroad), 111.8);
    addPlaceToPathway(new Tunnel("Chocen", 430, 1), 118.05, 430);
    addPlaceToPathway(new ShipLock("Dvorisko", 27.5, Direction::ToCrossroad), 122);
    addPlaceToPathway(new Bridge("Loucna", 770, Bridge::Type::TwoWay), 125.05, 770);
    addPlaceToPathway(new Tunnel("Vraclav", 240, 1), 128.93, 240);
    addPlaceToPathway(new ShipLock("Turov", 27.5, Direction::ToCrossroad), 139.3);
    addPlaceToPathway(new ShipLock("Cerna za B.", 27.5, Direction::ToCrossroad), 149.5);
    pardubice = addPlaceToPathway(new Port("Pardubice"), 159.7);
    labe = addPlaceToPathway(new RiverEnd("Labe"), 164.4);
}

Place* Model::startPathway(Place* origin, double distanceFromCrossroad, double length)
{
    crossroad->connect(origin, distanceFromCrossroad);
    currentPathwayPlace = origin;
    currentRiverKm = distanceFromCrossroad + length / 1000;
    return currentPathwayPlace;
}

Place* Model::addPlaceToPathway(Place* place, double riverKm, double length)
{
    currentPathwayPlace->connect(place, max(riverKm - currentRiverKm, 0));
    currentPathwayPlace = place;
    currentRiverKm = riverKm + length / 1000;
    return currentPathwayPlace;
}
