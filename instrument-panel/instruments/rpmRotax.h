#ifndef _RPM_ROTAX_H_
#define _RPM_ROTAX_H_

#include "simvars.h"
#include "instrument.h"

class rpmRotax : public instrument
{
private:
    SimVars* simVars;
    float scaleFactor;

    // Instrument values (calculated from variables and needed to draw the instrument)
    int digit1;
    int digit2;
    int digit3;
    int digit4;
    int digit5;
    double angle;

public:
    rpmRotax(int xPos, int yPos, int size, const char* parentName = NULL);
    void render();
    void update();

private:
    void resize();
    void addVars();
};

#endif // _RPM_ROTAX_H
