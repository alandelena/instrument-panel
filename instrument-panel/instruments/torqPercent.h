#ifndef _RPM_PERCENT_H_
#define _RPM_PERCENT_H_

#include "simvars.h"
#include "instrument.h"

class torqPercent : public instrument
{
private:
    SimVars* simVars;
    float scaleFactor;

    // Instrument values (calculated from variables and needed to draw the instrument)
    double angle;

public:
    torqPercent(int xPos, int yPos, int size, const char* parentName = NULL);
    void render();
    void update();

private:
    void resize();
    void addVars();
};

#endif // _RPM_SAVAGE_CUB_H
