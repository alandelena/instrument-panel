#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "engine.h"
#include "manPress.h"
#include "egtJet.h"
#include "itt.h"
#include "simvars.h"
#include "knobs.h"


/// <summary>
/// Construct a proxy to a MAP, EGT or ITT gauge based on engine and plane type
/// </summary>
engine::engine(int xPos, int yPos, int size) : instrument(xPos, yPos, size)
{
    setName("Engine");
    addVars();
    simVars = &globals.simVars->simVars;
    create();   
    resize();
}

/// <summary>
/// Create the custom instrument
/// </summary>
void engine::create()
{
    loadedAircraft = globals.aircraft;

    // Load custom instrument for this aircraft
    
    if (customInstrument) {
        delete customInstrument;
        customInstrument = NULL;
    }
    
    if ((int)simVars->engineType == 0) {
        // Instantiate a manifold pressure gauge for piston engines
        customInstrument = new manPress(xPos, yPos, size, name);
    }
    else if ((int)simVars->engineType == 1) {
        if (simVars->maxGrossWeight > 100000) { // pounds
            // Instantiate a EGT gauge for airliners
            customInstrument = new egtJet(xPos, yPos, size, name);
        } 
        else {
            // Instantiate a interstage turbine temp (ITT) gauge for lightweight jets
            customInstrument = new itt(xPos, yPos, size, name);        
        }    
    }
    else if ((int)simVars->engineType == 5) {
        // Instantiate a interstage turbine temp (ITT) gauge for turboprops
        customInstrument = new itt(xPos, yPos, size, name);        
    }
}

/// <summary>
/// Destroy and recreate all bitmaps as instrument has been resized
/// </summary>
void engine::resize()
{
    if (customInstrument) {
        customInstrument->render();
    }
}



/// <summary>
/// Draw the instrument at the stored position
/// </summary>
void engine::render()
{
    if (customInstrument) {
        customInstrument->render();
    }
}

/// <summary>
/// Fetch flightsim vars and then update all internal variables
/// that affect this instrument.
/// </summary>
void engine::update()
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
void engine::addVars()
{
    globals.simVars->addVar(name, "Max Gross Weight", false, 1, 0);
}
