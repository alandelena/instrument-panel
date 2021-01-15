#ifndef _POWER_H_
#define _POWER_H_

#include "simvars.h"
#include "instrument.h"

// power - a proxy for either a manifold pressure gauge or a percent N1 gauge.
class power : public instrument
{
private:
    SimVars* simVars;
    Aircraft loadedAircraft = NO_AIRCRAFT;

public:
    power(int xPos, int yPos, int size);
    void render();
    void update();

private:
    void create();
    void resize();
    void addVars();
};

#endif // _POWER_H
