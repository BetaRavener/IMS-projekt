/*
 * place.h
 *
 *  Created on: Nov 30, 2014
 *      Author: raven
 */

#ifndef PLACE_H_
#define PLACE_H_

#include <string>

class Ship;

enum class Direction {ToCrossroad, ToEndpoint};

class Place
{
public:
    Place();
    Place(std::string name);

    std::string getName();

    virtual void SailProcedure(Ship &ship) = 0;
    virtual void Output() = 0;

    virtual void connect(Place* place, double distance);
    Place* getNext(Direction dir, double* distance);

protected:
    virtual ~Place();

    Place* next;
    double nextDistance;

    std::string name;
private:
    Place* previous;
    double previousDistance;
};


#endif /* PLACE_H_ */
