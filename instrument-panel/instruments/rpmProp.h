#ifndef _RPM_PROP_H_
#define _RPM_PROP_H_

#include "simvars.h"
#include "instrument.h"

class rpmProp : public instrument
{
private:
    SimVars* simVars;
    Aircraft loadedAircraft = NO_AIRCRAFT;
    float scaleFactor;

    // Instrument values (caclulated from variables and needed to draw the instrument)
    int digit1;
    int digit2;
    int digit3;
    int digit4;
    int digit5;
    double angle;

public:
    rpmProp(int xPos, int yPos, int size, const char* parentName = NULL);
    void render();
    void update();

private:
    void resize();
    void addVars();
};

#endif // _RPM_PROP_H
