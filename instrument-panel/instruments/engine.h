#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "simvars.h"
#include "instrument.h"

// engine - a proxy for either a manifold pressure gauge or a percent N1 gauge.
class engine : public instrument
{
private:
    SimVars* simVars;
    Aircraft loadedAircraft = NO_AIRCRAFT;

public:
    engine(int xPos, int yPos, int size);
    void render();
    void update();

private:
    void create();
    void resize();
    void addVars();
};

#endif // _ENGINE_H
