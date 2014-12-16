//
//  voice.cpp
//  ripple
//
//  Created by Jakub Fiala on 11/12/2014.
//
//

#include "voice.h"


double Voice::oscOut(string type)
{
    vol = env.line(8, envData);
    if (type == "sine") {
        return osc.sinebuf(freq)*vol;
    }
    else if (type == "square") {
        return osc.square(freq)*vol;
    }
    else if (type == "saw") {
        return osc.saw(freq)*vol;
    }
    else if (type == "triangle") {
        return osc.triangle(freq)*vol;
    }
}

Voice::Voice(int midiNote, double * data)
{
    freq = converter.mtof(midiNote);
    active = true;
    envData = data;
}

void Voice::start()
{
    env.trigger(0, envData[0]);
}

void Voice::isActive() {
    return active;
}