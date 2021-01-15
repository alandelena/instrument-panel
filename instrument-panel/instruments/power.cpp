#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "power.h"
#include "rpmProp.h"
#include "rpmRotax.h"
#include "torqPercent.h"
#include "n1Percent.h"
#include "simvars.h"
#include "knobs.h"


/// <summary>
/// Construct a proxy to an RPM gauge for piston engines, a torque gauge for
/// turboprops, or a N1 gauge for jet engines.
/// </summary>
power::power(int xPos, int yPos, int size) : instrument(xPos, yPos, size)
{
    setName("Power");
    addVars();
    simVars = &globals.simVars->simVars;
    create();   
    resize();
}

/// <summary>
/// Create the custom instrument
/// </summary>
void power::create()
{
    loadedAircraft = globals.aircraft;

    // Load custom instrument for this aircraft
    
    if (customInstrument) {
        delete customInstrument;
        customInstrument = NULL;
    }
    
    if ((int)simVars->engineType == 0) {
        // Test for high-reving Rotax piston engine (e.g., Savage Cub, Shock Ultra, et al)
        if ((int)simVars->engineType == 0 && simVars->engineMaxRpm > 5000) {
            // Instantiate an engine RPM gauge 
            customInstrument = new rpmRotax(xPos, yPos, size, name);
        }
        else {
            // Instantiate a prop RPM gauge
            customInstrument = new rpmProp(xPos, yPos, size, name);
        }
    }
    else if ((int)simVars->engineType == 1) {
        // Instantiate an N1 percent gauge for jet engines
        customInstrument = new n1Percent(xPos, yPos, size, name);
    }
    else if ((int)simVars->engineType == 5) {
        // Instantiate a torque percent gauge for turboprop engines
        customInstrument = new torqPercent(xPos, yPos, size, name);
    }
}

/// <summary>
/// Destroy and recreate all bitmaps as instrument has been resized
/// </summary>
void power::resize()
{
    if (customInstrument) {
        customInstrument->render();
    }
}



/// <summary>
/// Draw the instrument at the stored position
/// </summary>
void power::render()
{
    if (customInstrument) {
        customInstrument->render();
    }
}

/// <summary>
/// Fetch flightsim vars and then update all internal variables
/// that affect this instrument.
/// </summary>
void power::update()
{
    // Check for aircraft change
    bool aircraftChanged = (loadedAircraft != globals.aircraft);
    if (aircraftChanged) {
        loadedAircraft = globals.aircraft;
        create();
    }

    if (customInstrument) {
        customInstrument->update();
    }
}

/// <summary>
/// Add FlightSim variables for this instrument (used for simulation mode)
/// </summary>
void power::addVars()
{
    globals.simVars->addVar(name, "Engine Type", false, 1, 0);
}
