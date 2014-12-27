//
//  voice.h
//  ripple
//
//  Created by Jakub Fiala on 11/12/2014.
//
//

#ifndef __ripple__voice__
#define __ripple__voice__

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"

class Voice {
    public:
        Voice(int midiNote, double * data);
        double oscOut(string type);
        void start();
        void stop();
        bool isActive();
        double freq;
        double vol;
        double note;
        maxiOsc osc;
        maxiEnvelope env;
        convert converter;
        Boolean active = false;
    
        double * envData;
};


#endif /* defined(__ripple__voice__) */
