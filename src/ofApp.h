#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxMaxim.h"
#include "ofxMidi.h"
#include "ofxGui.h"
#include "button.h"
#include "voice.h"
#include <deque>
#include <cmath>


class ofApp : public ofBaseApp{
    
public:
    ~ofApp();
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void audioRequested 	(float * input, int bufferSize, int nChannels);
    void audioReceived 	(float * input, int bufferSize, int nChannels);
    
    void tempoChanged(double & t);
    
    int		initialBufferSize;
    int		sampleRate;
    
    double outputs[2];
    ofxMaxiMix mix;
    
    
protected:
    ofxSlider<double> tempoSlider;
    
    Button buttons[28][16];
    Button play;
    Button midiOn;
    Button mappingButton;
    Button waveButton;
    Boolean playback;
    ofTrueTypeFont text;
    ofTrueTypeFont smalltext;
    
    double startTime, bpm;
    struct wave {
        Boolean isOn;
        int startX;
        int startY;
        int iteration;
    } newWave;
    void beat();
    void triggerStuff(int x, int y);
    
    double tempo;
    maxiOsc timer, synth;
    int time, ptime, voiceCount, curNote;
    maxiEnvelope adsr;
    convert converter;
    deque<Voice> voices;
    double adsrData[8] = {0,1,1.0,20,0.125,125,0,500};
    
    ofxMidiOut midiOut;
    Boolean isMidi;
    string mapping;
    string wavetype;
    
};

#endif
